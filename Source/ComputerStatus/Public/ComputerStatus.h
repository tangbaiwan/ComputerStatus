// Copyright 2023 Device. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FComputerStatusModule : public IModuleInterface
{
public:

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
