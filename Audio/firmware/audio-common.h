#ifndef __AUDIO_COMMON_H__
#define __AUDIO_COMMON_H__

enum
{
	Command_None =				0,
	Command_FrameCountBegin =	1,
	Command_Sync =				2,
	Command_IdentifyEndpoint =	3,
	Command_SetAttenuation =	4,
	Command_SetLowPassCorner =	5,
	Command_SetHighPassCorner =	6,
	Command_SetVisualEffects =	7,
};

#endif // __AUDIO_COMMON_H__
