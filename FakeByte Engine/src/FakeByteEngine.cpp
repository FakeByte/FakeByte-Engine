#include "FakeByteEngine.h"
#include "ECS\Core\SystemManager.h"
#include "Time\Timer.h"

void FakeByteEngine::Initialize() {
	GetInstance().InitializeImplementation();
}

void FakeByteEngine::InitializeImplementation() {
	SetFloatingPointControl();
	initialized = true;
}

void FakeByteEngine::Start() {
	GetInstance().StartImplementation();
}

void FakeByteEngine::StartImplementation() {
	if (initialized) {
		GameLoop();
	}
}

void FakeByteEngine::Quit() {
	GetInstance().QuitImplementation();
}

void FakeByteEngine::QuitImplementation() {
	quit = true;
}

void FakeByteEngine::GameLoop() {
	while (!quit) {
		Timer gameloopTimer("Gameloop");
		/*****************************************************************
		Assert if our deterministic floating point settings are unchanged, 
		different libraries/devices can change those settings
		If values are changed we reset the values to our configuration
		******************************************************************/
		SetFloatingPointControl();

		SystemManager::Step();
	}
}

/**********************************************************
Floating Point Determinism Control, Compile with /fp:strict
-Sets Rounding Control to nearest and Denormal Control
-asserts if the intermediate precision is controlled by the types used
Those settings should give floating point determinism on x64
**********************************************************/
void FakeByteEngine::SetFloatingPointControl() {
	unsigned int control_word;
	int err;

	if ((!(_controlfp_s(&control_word, 0, 0) & _MCW_RC) == _RC_NEAR) ||
		!((_controlfp_s(&control_word, 0, 0) & _MCW_DN) == _DN_SAVE)) {
		//TODO:Error Logging

		// Get original FP control word
		err = _controlfp_s(&control_word, 0, 0);
		assert(!err && "Couldn't retrieve FP control word");

		// Set Denormal control to save
		err = _controlfp_s(&control_word, _DN_SAVE, _MCW_DN);
		assert(!err && "Couldn't set denormal control to save");

		//Set Rounding control to nearest
		err = _controlfp_s(&control_word, _RC_NEAR, _MCW_RC);
		assert(!err && "Couldn't set rounding control to nearest");
	}

	/*
	FLT_EVAL_METHOD values, 0 is good for determinism
	0: intermediate precision is dictated by the types used
	1: intermediate precision is double precision (unless the types used are higher precision)
	2: intermediate precision is long double
	*/
	assert(FLT_EVAL_METHOD == 0 && "Intermediate precision is not dictated by the types used");
}
