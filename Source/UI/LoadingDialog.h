
#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class LoadingDialog : public ThreadWithProgressWindow
{
public:
	LoadingDialog();
	~LoadingDialog();

	void run() override;
	void threadComplete(bool userPressedCancel) override;


};