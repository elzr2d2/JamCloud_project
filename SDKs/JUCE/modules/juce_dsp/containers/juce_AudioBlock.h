/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2017 - ROLI Ltd.

   JUCE is an open source library subject to commercial or open-source
   licensing.

   By using JUCE, you agree to the terms of both the JUCE 5 End-User License
   Agreement and JUCE 5 Privacy Policy (both updated and effective as of the
   27th April 2017).

   End User License Agreement: www.juce.com/juce-5-licence
   Privacy Policy: www.juce.com/juce-5-privacy-policy

   Or: You may also use this code under the terms of the GPL v3 (see
   www.gnu.org/licenses).

   JUCE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER
   EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE
   DISCLAIMED.

  ==============================================================================
*/

namespace juce
{
namespace dsp
{

#ifndef DOXYGEN
namespace SampleTypeHelpers // Internal classes needed for handling sample type classes
{
    template <typename T, bool = std::is_floating_point<T>::value>
    struct ElementType
    {
        using Type = T;
    };

    template <typename T>
    struct ElementType<T, false>
    {
        using Type = typename T::value_type;
    };
}
#endif

//==============================================================================
/**
    Minimal and lightweight data-structure which contains a list of pointers to
    channels containing some kind of sample data.

    This class doesn't own any of the data which it points to, it's simply a view
    into data that is owned elsewhere. You can construct one from some raw data
    that you've allocated yourself, or give it a HeapBlock to use, or give it
    an AudioBuffer which it can refer to, but in all cases the user is
    responsible for making sure that the data doesn't get deleted while there's
    still an AudioBlock using it.

    @tags{DSP}
*/
template <typename SampleType>
class AudioBlock
{
private:
    template <typename OtherSampleType>
    using MayUseConvertingConstructor =
        std::enable_if_t<std::is_same<std::remove_const_t<SampleType>,
                                      std::remove_const_t<OtherSampleType>>::value
                             && std::is_const<SampleType>::value
                             && ! std::is_const<OtherSampleType>::value,
                         int>;

public:
    //==============================================================================
    using NumericType = typename SampleTypeHelpers::ElementType<SampleType>::Type;

    //==============================================================================
    /** Create a zero-sized AudioBlock. */
    forcedinline AudioBlock() noexcept = default;

    /** Creates an AudioBlock from a pointer to an array of channels.
        AudioBlock does not copy nor own the memory pointed to by dataToUse.
        Therefore it is the user's responsibility to ensure that the memory is retained
        throughout the life-time of the AudioBlock and released when no longer needed.
    */
    forcedinline AudioBlock (SampleType* const* channelData,
                             size_t numberOfChannels, size_t numberOfSamples) noexcept
        : channels (channelData),
          numChannels (static_cast<ChannelCountType> (numberOfChannels)),
          numSamples (numberOfSamples)
    {
    }

    /** Creates an AudioBlock from a pointer to an array of channels.
        AudioBlock does not copy nor own the memory pointed to by dataToUse.
        Therefore it is the user's responsibility to ensure that the memory is retained
        throughout the life-time of the AudioBlock and released when no longer needed.
    */
    forcedinline AudioBlock (SampleType* const* channelData, size_t numberOfChannels,
                             size_t startSampleIndex, size_t numberOfSamples) noexcept
        : channels (channelData),
          numChannels (static_cast<ChannelCountType> (numberOfChannels)),
          startSample (startSampleIndex),
          numSamples (numberOfSamples)
    {
    }

    /** Allocates a suitable amount of space in a HeapBlock, and initialises this object
        to point into it.
        The HeapBlock must of course not be freed or re-allocated while this object is still in
        use, because it will be referencing its data.
    */
    AudioBlock (HeapBlock<char>& heapBlockToUseForAllocation,
                size_t numberOfChannels, size_t numberOfSamples,
                size_t alignmentInBytes = defaultAlignment) noexcept
        : numChannels (static_cast<ChannelCountType> (numberOfChannels)),
          numSamples (numberOfSamples)
    {
        auto roundedUpNumSamples = (numberOfSamples + elementMask) & ~elementMask;
        auto channelSize = sizeof (SampleType) * roundedUpNumSamples;
        auto channelListBytes = sizeof (SampleType*) * numberOfChannels;
        auto extraBytes = alignmentInBytes - 1;

        heapBlockToUseForAllocation.malloc (channelListBytes + extraBytes + channelSize * numberOfChannels);

        auto* chanArray = reinterpret_cast<SampleType**> (heapBlockToUseForAllocation.getData());
        channels = chanArray;

        auto* data = reinterpret_cast<SampleType*> (addBytesToPointer (chanArray, channelListBytes));
        data = snapPointerToAlignment (data, alignmentInBytes);

        for (ChannelCountType i = 0; i < numChannels; ++i)
        {
            chanArray[i] = data;
            data += roundedUpNumSamples;
        }
    }

    /** Creates an AudioBlock that points to the data in an AudioBuffer.
        AudioBlock does not copy nor own the memory pointed to by dataToUse.
        Therefore it is the user's responsibility to ensure that the buffer is retained
        throughout the life-time of the AudioBlock without being modified.
    */
    template <typename OtherSampleType>
    AudioBlock (AudioBuffer<OtherSampleType>& buffer) noexcept
        : channels (buffer.getArrayOfWritePointers()),
          numChannels (static_cast<ChannelCountType> (buffer.getNumChannels())),
          numSamples (static_cast<size_t> (buffer.getNumSamples()))
    {
    }

    /** Creates an AudioBlock that points to the data in an AudioBuffer.
        AudioBlock does not copy nor own the memory pointed to by dataToUse.
        Therefore it is the user's responsibility to ensure that the buffer is retained
        throughout the life-time of the AudioBlock without being modified.
    */
    template <typename OtherSampleType>
    AudioBlock (AudioBuffer<OtherSampleType>& buffer, size_t startSampleIndex) noexcept
        : channels (buffer.getArrayOfWritePointers()),
          numChannels (static_cast<ChannelCountType> (buffer.getNumChannels())),
          startSample (startSampleIndex),
          numSamples (static_cast<size_t> (buffer.getNumSamples()) - startSampleIndex)
    {
        jassert (startSample < static_cast<size_t> (buffer.getNumSamples()));
    }

    AudioBlock (const AudioBlock& other) noexcept = default;
    AudioBlock& operator= (const AudioBlock& other) noexcept = default;

    template <typename OtherSampleType, MayUseConvertingConstructor<OtherSampleType> = 0>
    AudioBlock (const AudioBlock<OtherSampleType>& other) noexcept
        : channels { other.channels },
          numChannels { other.numChannels },
          startSample { other.startSample },
          numSamples { other.numSamples }
    {
    }

    template <typename OtherSampleType, MayUseConvertingConstructor<OtherSampleType> = 0>
    AudioBlock& operator= (const AudioBlock<OtherSampleType>& other) noexcept
    {
        AudioBlock blockCopy { other };
        swap (blockCopy);
        return *this;
    }

    void swap (AudioBlock& other) noexcept
    {
        std::swap (other.channels, channels);
        std::swap (other.numChannels, numChannels);
        std::swap (other.startSample, startSample);
        std::swap (other.numSamples, numSamples);
    }

    //==============================================================================
    template <typename OtherSampleType>
    bool operator== (const AudioBlock<OtherSampleType>& other) const noexcept
    {
        return std::equal (channels,
                           channels + numChannels,
                           other.channels,
                           other.channels + other.numChannels)
               && startSample == other.startSample
               && numSamples == other.numSamples;
    }

    template <typename OtherSampleType>
    bool operator!= (const AudioBlock<OtherSampleType>& other) const noexcept
    {
        return ! (*this == other);
    }

    //==============================================================================
    forcedinline size_t getNumSamples() const noexcept           { return numSamples; }
    forcedinline size_t getNumChannels() const noexcept          { return static_cast<size_t> (numChannels); }

    /** Returns a raw pointer into one of the channels in this block. */
    forcedinline const SampleType* getChannelPointer (size_t channel) const noexcept
    {
        jassert (channel < numChannels);
        jassert (numSamples > 0);
        return channels[channel] + startSample;
    }

    /** Returns a raw pointer into one of the channels in this block. */
    forcedinline SampleType* getChannelPointer (size_t channel) noexcept
    {
        jassert (channel < numChannels);
        jassert (numSamples > 0);
        return channels[channel] + startSample;
    }

    /** Returns an AudioBlock that represents one of the channels in this block. */
    forcedinline AudioBlock getSingleChannelBlock (size_t channel) const noexcept
    {
        jassert (channel < numChannels);
        return AudioBlock (channels + channel, 1, startSample, numSamples);
    }

    /** Returns a subset of continguous channels
        @param channelStart       First channel of the subset
        @param numChannelsToUse   Count of channels in the subset
    */
    forcedinline AudioBlock getSubsetChannelBlock (size_t channelStart, size_t numChannelsToUse) const noexcept
    {
        jassert (channelStart < numChannels);
        jassert ((channelStart + numChannelsToUse) <= numChannels);

        return AudioBlock (channels + channelStart, numChannelsToUse, startSample, numSamples);
    }

    /** Returns a sample from the buffer.
        The channel and index are not checked - they are expected to be in-range. If not,
        an assertion will be thrown, but in a release build, you're into 'undefined behaviour'
        territory.
    */
    SampleType getSample (int channel, int sampleIndex) const noexcept
    {
        jassert (isPositiveAndBelow (channel, numChannels));
        jassert (isPositiveAndBelow (sampleIndex, numSamples));
        return channels[channel][startSample + sampleIndex];
    }

    /** Modifies a sample in the buffer.
        The channel and index are not checked - they are expected to be in-range. If not,
        an assertion will be thrown, but in a release build, you're into 'undefined behaviour'
        territory.
    */
    void setSample (int destChannel, int destSample, SampleType newValue) noexcept
    {
        jassert (isPositiveAndBelow (destChannel, numChannels));
        jassert (isPositiveAndBelow (destSample, numSamples));
        channels[destChannel][startSample + destSample] = newValue;
    }

    /** Adds a value to a sample in the buffer.
        The channel and index are not checked - they are expected to be in-range. If not,
        an assertion will be thrown, but in a release build, you're into 'undefined behaviour'
        territory.
    */
    void addSample (int destChannel, int destSample, SampleType valueToAdd) noexcept
    {
        jassert (isPositiveAndBelow (destChannel, numChannels));
        jassert (isPositiveAndBelow (destSample, numSamples));
        channels[destChannel][startSample + destSample] += valueToAdd;
    }

    //==============================================================================
    /** Clear the memory described by this AudioBlock. */
    forcedinline AudioBlock& clear() noexcept
    {
        auto n = static_cast<int> (numSamples * sizeFactor);

        for (size_t ch = 0; ch < numChannels; ++ch)
            FloatVectorOperations::clear (channelPtr (ch), n);

        return *this;
    }

    /** Fill memory with value. */
    forcedinline AudioBlock& JUCE_VECTOR_CALLTYPE fill (SampleType value) noexcept
    {
        auto n = static_cast<int> (numSamples * sizeFactor);

        for (size_t ch = 0; ch < numChannels; ++ch)
            FloatVectorOperations::fill (channelPtr (ch), value, n);

        return *this;
    }

    /** Copy the values in src to the receiver. */
    template <typename OtherSampleType>
    forcedinline AudioBlock& copy (const AudioBlock<OtherSampleType>& src) noexcept
    {
        auto maxChannels = jmin (src.numChannels, numChannels);
        auto n = static_cast<int> (jmin (src.numSamples, numSamples) * sizeFactor);

        for (size_t ch = 0; ch < maxChannels; ++ch)
            FloatVectorOperations::copy (channelPtr (ch), src.channelPtr (ch), n);

        return *this;
    }

    /** Copy the values from a JUCE's AudioBuffer to the receiver.

        All indices and sizes are in the receiver's units, i.e. if SampleType is a
        SIMDRegister then incrementing srcPos by one will increase the sample position
        in the AudioBuffer's units by a factor of SIMDRegister<SampleType>::SIMDNumElements.
    */
    forcedinline AudioBlock& copyFrom (const AudioBuffer<NumericType>& src, size_t srcPos = 0, size_t dstPos = 0,
                                       size_t numElements = std::numeric_limits<size_t>::max())
    {
        auto srclen = static_cast<size_t> (src.getNumSamples()) / sizeFactor;
        auto n = static_cast<int> (jmin (srclen - srcPos, numSamples - dstPos, numElements) * sizeFactor);
        auto maxChannels = jmin (static_cast<size_t> (src.getNumChannels()), static_cast<size_t> (numChannels));

        for (size_t ch = 0; ch < maxChannels; ++ch)
            FloatVectorOperations::copy (channelPtr (ch) + dstPos,
                                         src.getReadPointer (static_cast<int> (ch),
                                                             static_cast<int> (srcPos * sizeFactor)),
                                         n);

        return *this;
    }

    /** Copy the values from the receiver to a JUCE's AudioBuffer.

        All indices and sizes are in the receiver's units, i.e. if SampleType is a
        SIMDRegister then incrementing dstPos by one will increase the sample position
        in the AudioBuffer's units by a factor of SIMDRegister<SampleType>::SIMDNumElements.
    */
    forcedinline const AudioBlock& copyTo (AudioBuffer<NumericType>& dst, size_t srcPos = 0, size_t dstPos = 0,
                                           size_t numElements = std::numeric_limits<size_t>::max()) const
    {
        auto dstlen = static_cast<size_t> (dst.getNumSamples()) / sizeFactor;
        auto n = static_cast<int> (jmin (numSamples - srcPos, dstlen - dstPos, numElements) * sizeFactor);
        auto maxChannels = jmin (static_cast<size_t> (dst.getNumChannels()), static_cast<size_t> (numChannels));

        for (size_t ch = 0; ch < maxChannels; ++ch)
            FloatVectorOperations::copy (dst.getWritePointer (static_cast<int> (ch),
                                                              static_cast<int> (dstPos * sizeFactor)),
                                         channelPtr (ch) + srcPos, n);

        return *this;
    }

    /** Move memory within the receiver from the position srcPos to the position dstPos.
        If numElements is not specified then move will move the maximum amount of memory.
    */
    forcedinline AudioBlock& move (size_t srcPos, size_t dstPos,
                                   size_t numElements = std::numeric_limits<size_t>::max()) noexcept
    {
        jassert (srcPos <= numSamples && dstPos <= numSamples);
        auto len = jmin (numSamples - srcPos, numSamples - dstPos, numElements) * sizeof (SampleType);

        if (len != 0)
            for (size_t ch = 0; ch < numChannels; ++ch)
                ::memmove (getChannelPointer (ch) + dstPos,
                           getChannelPointer (ch) + srcPos, len);

        return *this;
    }

    //==============================================================================
    /** Return a new AudioBlock pointing to a sub-block inside the receiver. This
        function does not copy the memory and you must ensure that the original memory
        pointed to by the receiver remains valid through-out the life-time of the
        returned sub-block.

        @param newOffset   The index of an element inside the receiver which will
                           will become the first element of the return value.
        @param newLength   The number of elements of the newly created sub-block.
    */
    inline AudioBlock getSubBlock (size_t newOffset, size_t newLength) const noexcept
    {
        jassert (newOffset < numSamples);
        jassert (newOffset + newLength <= numSamples);

        return AudioBlock (channels, numChannels, startSample + newOffset, newLength);
    }

    /** Return a new AudioBlock pointing to a sub-block inside the receiver. This
        function does not copy the memory and you must ensure that the original memory
        pointed to by the receiver remains valid through-out the life-time of the
        returned sub-block.

        @param newOffset   The index of an element inside the receiver which will
                           will become the first element of the return value.
                           The return value will include all subsequent elements
                           of the receiver.
    */
    inline AudioBlock getSubBlock (size_t newOffset) const noexcept
    {
        return getSubBlock (newOffset, getNumSamples() - newOffset);
    }

    //==============================================================================
    /** Adds a fixed value to the receiver. */
    forcedinline AudioBlock& JUCE_VECTOR_CALLTYPE add (SampleType value) noexcept
    {
        auto n = static_cast<int> (numSamples * sizeFactor);

        for (size_t ch = 0; ch < numChannels; ++ch)
            FloatVectorOperations::add (channelPtr (ch), value, n);

        return *this;
    }

    /** Adds the source values to the receiver. */
    template <typename OtherSampleType>
    forcedinline AudioBlock& add (AudioBlock<OtherSampleType> src) noexcept
    {
        jassert (numChannels == src.numChannels);
        auto n = static_cast<int> (jmin (numSamples, src.numSamples) * sizeFactor);

        for (size_t ch = 0; ch < numChannels; ++ch)
            FloatVectorOperations::add (channelPtr (ch), src.channelPtr (ch), n);

        return *this;
    }

    /** Adds a fixed value to each source value and stores it in the destination array of the receiver. */
    template <typename OtherSampleType>
    forcedinline AudioBlock& JUCE_VECTOR_CALLTYPE add (AudioBlock<OtherSampleType> src, SampleType value) noexcept
    {
        jassert (numChannels == src.numChannels);
        auto n = static_cast<int> (jmin (numSamples, src.numSamples) * sizeFactor);

        for (size_t ch = 0; ch < numChannels; ++ch)
            FloatVectorOperations::add (channelPtr (ch), src.channelPtr (ch), value, n);

        return *this;
    }

    /** Adds each source1 value to the corresponding source2 value and stores it in the destination array of the receiver. */
    template <typename Src1SampleType, typename Src2SampleType>
    forcedinline AudioBlock& add (AudioBlock<Src1SampleType> src1, AudioBlock<Src2SampleType> src2) noexcept
    {
        jassert (numChannels == src1.numChannels && src1.numChannels == src2.numChannels);
        auto n = static_cast<int> (jmin (numSamples, src1.numSamples, src2.numSamples) * sizeFactor);

        for (size_t ch = 0; ch < numChannels; ++ch)
            FloatVectorOperations::add (channelPtr (ch), src1.channelPtr (ch), src2.getChannelPointer (ch), n);

        return *this;
    }

    /** Subtracts a fixed value from the receiver. */
    forcedinline AudioBlock& JUCE_VECTOR_CALLTYPE subtract (SampleType value) noexcept
    {
        return add (value * static_cast<SampleType> (-1.0));
    }

    /** Subtracts the source values from the receiver. */
    template <typename OtherSampleType>
    forcedinline AudioBlock& subtract (AudioBlock<OtherSampleType> src) noexcept
    {
        jassert (numChannels == src.numChannels);
        auto n = static_cast<int> (jmin (numSamples, src.numSamples) * sizeFactor);

        for (size_t ch = 0; ch < numChannels; ++ch)
            FloatVectorOperations::subtract (channelPtr (ch), src.channelPtr (ch), n);

        return *this;
    }

    /** Subtracts a fixed value from each source value and stores it in the destination array of the receiver. */
    template <typename OtherSampleType>
    forcedinline AudioBlock& JUCE_VECTOR_CALLTYPE subtract (AudioBlock<OtherSampleType> src, SampleType value) noexcept
    {
        return add (src, static_cast<SampleType> (-1.0) * value);
    }

    /** Subtracts each source2 value from the corresponding source1 value and stores it in the destination array of the receiver. */
    template <typename Src1SampleType, typename Src2SampleType>
    forcedinline AudioBlock& subtract (AudioBlock<Src1SampleType> src1, AudioBlock<Src2SampleType> src2) noexcept
    {
        jassert (numChannels == src1.numChannels && src1.numChannels == src2.numChannels);
        auto n = static_cast<int> (jmin (numSamples, src1.numSamples, src2.numSamples) * sizeFactor);

        for (size_t ch = 0; ch < numChannels; ++ch)
            FloatVectorOperations::subtract (channelPtr (ch), src1.channelPtr (ch), src2.channelPtr (ch), n);

        return *this;
    }

    /** Multiplies a fixed value to the receiver. */
    forcedinline AudioBlock& JUCE_VECTOR_CALLTYPE multiply (SampleType value) noexcept
    {
        auto n = static_cast<int> (numSamples * sizeFactor);

        for (size_t ch = 0; ch < numChannels; ++ch)
            FloatVectorOperations::multiply (channelPtr (ch), value, n);

        return *this;
    }

    /** Multiplies the source values to the receiver. */
    template <typename OtherSampleType>
    forcedinline AudioBlock& multiply (AudioBlock<OtherSampleType> src) noexcept
    {
        jassert (numChannels == src.numChannels);
        auto n = static_cast<int> (jmin (numSamples, src.numSamples) * sizeFactor);

        for (size_t ch = 0; ch < numChannels; ++ch)
            FloatVectorOperations::multiply (channelPtr (ch), src.channelPtr (ch), n);

        return *this;
    }

    /** Multiplies a fixed value to each source value and stores it in the destination array of the receiver. */
    template <typename OtherSampleType>
    forcedinline AudioBlock& JUCE_VECTOR_CALLTYPE multiply (AudioBlock<OtherSampleType> src, SampleType value) noexcept
    {
        jassert (numChannels == src.numChannels);
        auto n = static_cast<int> (jmin (numSamples, src.numSamples) * sizeFactor);

        for (size_t ch = 0; ch < numChannels; ++ch)
            FloatVectorOperations::multiply (channelPtr (ch), src.channelPtr (ch), value, n);

        return *this;
    }

    /** Multiplies each source1 value to the corresponding source2 value and stores it in the destination array of the receiver. */
    template <typename Src1SampleType, typename Src2SampleType>
    forcedinline AudioBlock& multiply (AudioBlock<Src1SampleType> src1, AudioBlock<Src2SampleType> src2) noexcept
    {
        jassert (numChannels == src1.numChannels && src1.numChannels == src2.numChannels);
        auto n = static_cast<int> (jmin (numSamples, src1.numSamples, src2.numSamples) * sizeFactor);

        for (size_t ch = 0; ch < numChannels; ++ch)
            FloatVectorOperations::multiply (channelPtr (ch), src1.channelPtr (ch), src2.channelPtr (ch), n);

        return *this;
    }

    /** Multiplies all channels of the AudioBlock by a smoothly changing value and stores them . */
    template <typename SmoothingType>
    AudioBlock& multiply (SmoothedValue<SampleType, SmoothingType>& value) noexcept
    {
        if (! value.isSmoothing())
        {
            *this *= value.getTargetValue();
        }
        else
        {
            for (size_t i = 0; i < numSamples; ++i)
            {
                const auto scaler = value.getNextValue();

                for (size_t ch = 0; ch < numChannels; ++ch)
                    channelPtr (ch)[i] *= scaler;
            }
        }

        return *this;
    }

    /** Multiplies all channels of the source by a smoothly changing value and stores them in the receiver. */
    template <typename OtherSampleType, typename SmoothingType>
    AudioBlock& multiply (AudioBlock<OtherSampleType> src, SmoothedValue<SampleType, SmoothingType>& value) noexcept
    {
        jassert (numChannels == src.numChannels);

        if (! value.isSmoothing())
        {
            multiply (src, value.getTargetValue());
        }
        else
        {
            auto n = jmin (numSamples, src.numSamples) * sizeFactor;

            for (size_t i = 0; i < n; ++i)
            {
                const auto scaler = value.getNextValue();

                for (size_t ch = 0; ch < numChannels; ++ch)
                    channelPtr (ch)[i] = scaler * src.getChannelPointer (ch)[i];
            }
        }

        return *this;
    }

    /** Multiplies each value in src with factor and adds the result to the receiver. */
    template <typename OtherSampleType>
    forcedinline AudioBlock& JUCE_VECTOR_CALLTYPE addWithMultiply (AudioBlock<OtherSampleType> src, SampleType factor) noexcept
    {
        jassert (numChannels == src.numChannels);
        auto n = static_cast<int> (jmin (numSamples, src.numSamples) * sizeFactor);

        for (size_t ch = 0; ch < numChannels; ++ch)
            FloatVectorOperations::addWithMultiply (channelPtr (ch), src.channelPtr (ch), factor, n);

        return *this;
    }

    /** Multiplies each value in srcA with the corresponding value in srcB and adds the result to the receiver. */
    template <typename Src1SampleType, typename Src2SampleType>
    forcedinline AudioBlock& addWithMultiply (AudioBlock<Src1SampleType> src1, AudioBlock<Src2SampleType> src2) noexcept
    {
        jassert (numChannels == src1.numChannels && src1.numChannels == src2.numChannels);
        auto n = static_cast<int> (jmin (numSamples, src1.numSamples, src2.numSamples) * sizeFactor);

        for (size_t ch = 0; ch < numChannels; ++ch)
            FloatVectorOperations::addWithMultiply (channelPtr (ch), src1.channelPtr (ch), src2.channelPtr (ch), n);

        return *this;
    }

    /** Negates each value of the receiver. */
    forcedinline AudioBlock& negate() noexcept
    {
        return multiply (static_cast<SampleType> (-1.0));
    }

    /** Negates each value of source and stores it in the receiver. */
    template <typename OtherSampleType>
    forcedinline AudioBlock& replaceWithNegativeOf (AudioBlock<OtherSampleType> src) noexcept
    {
        jassert (numChannels == src.numChannels);
        auto n = static_cast<int> (jmin (numSamples, src.numSamples) * sizeFactor);

        for (size_t ch = 0; ch < numChannels; ++ch)
            FloatVectorOperations::negate (channelPtr (ch), src.channelPtr (ch), n);

        return *this;
    }

    /** Takes the absolute value of each element of src and stores it inside the receiver. */
    template <typename OtherSampleType>
    forcedinline AudioBlock& replaceWithAbsoluteValueOf (AudioBlock<OtherSampleType> src) noexcept
    {
        jassert (numChannels == src.numChannels);
        auto n = static_cast<int> (jmin (numSamples, src.numSamples) * sizeFactor);

        for (size_t ch = 0; ch < numChannels; ++ch)
            FloatVectorOperations::abs (channelPtr (ch), src.channelPtr (ch), n);

        return *this;
    }

    /** Each element of receiver will be the minimum of the corresponding element of the source arrays. */
    template <typename Src1SampleType, typename Src2SampleType>
    forcedinline AudioBlock& min (AudioBlock<Src1SampleType> src1, AudioBlock<Src2SampleType> src2) noexcept
    {
        jassert (numChannels == src1.numChannels && src1.numChannels == src2.numChannels);
        auto n = static_cast<int> (jmin (src1.numSamples, src2.numSamples, numSamples) * sizeFactor);

        for (size_t ch = 0; ch < numChannels; ++ch)
            FloatVectorOperations::min (channelPtr (ch), src1.channelPtr (ch), src2.channelPtr (ch), n);

        return *this;
    }

    /** Each element of the receiver will be the maximum of the corresponding element of the source arrays. */
    template <typename Src1SampleType, typename Src2SampleType>
    forcedinline AudioBlock& max (AudioBlock<Src1SampleType> src1, AudioBlock<Src2SampleType> src2) noexcept
    {
        jassert (numChannels == src1.numChannels && src1.numChannels == src2.numChannels);
        auto n = static_cast<int> (jmin (src1.numSamples, src2.numSamples, numSamples) * sizeFactor);

        for (size_t ch = 0; ch < numChannels; ++ch)
            FloatVectorOperations::max (channelPtr (ch), src1.channelPtr (ch), src2.channelPtr (ch), n);

        return *this;
    }

    /** Finds the minimum and maximum value of the buffer. */
    forcedinline Range<NumericType> findMinAndMax() const noexcept
    {
        if (numChannels == 0)
            return {};

        auto n = static_cast<int> (numSamples * sizeFactor);
        auto minmax = FloatVectorOperations::findMinAndMax (channelPtr (0), n);

        for (size_t ch = 1; ch < numChannels; ++ch)
            minmax = minmax.getUnionWith (FloatVectorOperations::findMinAndMax (channelPtr (ch), n));

        return minmax;
    }

    //==============================================================================
    // convenient operator wrappers
    forcedinline AudioBlock& JUCE_VECTOR_CALLTYPE operator+= (SampleType src) noexcept   { return add (src); }
    forcedinline AudioBlock&                      operator+= (AudioBlock src) noexcept   { return add (src); }
    forcedinline AudioBlock& JUCE_VECTOR_CALLTYPE operator-= (SampleType src) noexcept   { return subtract (src); }
    forcedinline AudioBlock&                      operator-= (AudioBlock src) noexcept   { return subtract (src); }
    forcedinline AudioBlock& JUCE_VECTOR_CALLTYPE operator*= (SampleType src) noexcept   { return multiply (src); }
    forcedinline AudioBlock&                      operator*= (AudioBlock src) noexcept   { return multiply (src); }
    template <typename SmoothingType>
    forcedinline AudioBlock&                      operator*= (SmoothedValue<SampleType, SmoothingType>& value) noexcept   { return multiply (value); }

    //==============================================================================
    // This class can only be used with floating point types
    static_assert (std::is_same<std::remove_const_t<SampleType>, float>::value
                    || std::is_same<std::remove_const_t<SampleType>, double>::value
                  #if JUCE_USE_SIMD
                    || std::is_same<std::remove_const_t<SampleType>, SIMDRegister<float>>::value
                    || std::is_same<std::remove_const_t<SampleType>, SIMDRegister<double>>::value
                  #endif
                   , "AudioBlock only supports single or double precision floating point types");

    //==============================================================================
    /** Applies a function to each value in an input block, putting the result into an output block.
        The function supplied must take a SampleType as its parameter, and return a SampleType.
        The two blocks must have the same number of channels and samples.
    */
    template <typename Src1SampleType, typename Src2SampleType, typename FunctionType>
    static void process (AudioBlock<Src1SampleType> inBlock, AudioBlock<Src2SampleType> outBlock, FunctionType&& function)
    {
        auto len = inBlock.getNumSamples();
        auto numChans = inBlock.getNumChannels();

        jassert (len == outBlock.getNumSamples());
        jassert (numChans == outBlock.getNumChannels());

        for (ChannelCountType c = 0; c < numChans; ++c)
        {
            auto* src = inBlock.getChannelPointer (c);
            auto* dst = outBlock.getChannelPointer (c);

            for (size_t i = 0; i < len; ++i)
                dst[i] = function (src[i]);
        }
    }

private:
    //==============================================================================
    NumericType*       channelPtr (size_t ch) noexcept          { return reinterpret_cast<NumericType*>       (getChannelPointer (ch)); }
    const NumericType* channelPtr (size_t ch) const noexcept    { return reinterpret_cast<const NumericType*> (getChannelPointer (ch)); }

    //==============================================================================
    using ChannelCountType = unsigned int;

    //==============================================================================
    static constexpr size_t sizeFactor    = sizeof (SampleType) / sizeof (NumericType);
    static constexpr size_t elementMask   = sizeFactor - 1;
    static constexpr size_t byteMask      = (sizeFactor * sizeof (NumericType)) - 1;

   #if JUCE_USE_SIMD
    static constexpr size_t defaultAlignment = sizeof (SIMDRegister<NumericType>);
   #else
    static constexpr size_t defaultAlignment = sizeof (NumericType);
   #endif

    SampleType* const* channels;
    ChannelCountType numChannels = 0;
    size_t startSample = 0, numSamples = 0;

    template <typename OtherSampleType>
    friend class AudioBlock;
};

} // namespace dsp
} // namespace juce
