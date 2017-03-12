#include "main.h"

struct AdminSetting A_Set;

void initAdminSettings()
{
	A_Set.iAmmoCount = 20;//get ini
	A_Set.Tracers.reserve(A_Set.iAmmoCount);
	A_Set.traces = true;//get ini
}