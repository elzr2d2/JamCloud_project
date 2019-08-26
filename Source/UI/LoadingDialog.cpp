#include "LoadingDialog.h"

LoadingDialog::LoadingDialog():ThreadWithProgressWindow("busy doing some important things...", true, false)
{
	launchThread();
	setStatusMessage("Getting ready...");
}

LoadingDialog::~LoadingDialog()
{
}

void LoadingDialog::run()
{
	setProgress(-1.0); // setting a value beyond the range 0 -> 1 will show a spinning bar..
	setStatusMessage("Preparing to do some stuff...");
	wait(1000);

	int thingsToDo = 10;

	for (int i = 0; i < thingsToDo; ++i)
	{
		// must check this as often as possible, because this is
		// how we know if the user's pressed 'cancel'

		if (threadShouldExit())
			return;

		// this will update the progress bar on the dialog box
		setProgress(i / (double)thingsToDo);

		setStatusMessage(String(thingsToDo - i) + " things left to do...");

		wait(250);

		setProgress(-1.0); // setting a value beyond the range 0 -> 1 will show a spinning bar..
		setStatusMessage("Finishing off the last few bits and pieces!");
		wait(500);
	}
}

void LoadingDialog::threadComplete(bool userPressedCancel)
{
	if (userPressedCancel)
	{
		AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon,
			"Progress window",
			"You pressed cancel!");
	}
	else
	{
		// thread finished normally..
		AlertWindow::showMessageBoxAsync(AlertWindow::AlertIconType::NoIcon,
			"Welcome To JamCloud",
			"let's get Funky (;");
	}

	// ..and clean up by deleting our thread object..
	//delete this;
	
}
