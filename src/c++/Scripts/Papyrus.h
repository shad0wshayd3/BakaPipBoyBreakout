#pragma once

#include "MCM/MCM.h"

namespace Papyrus
{
	class BakaFullscreenPipboy
	{
	public:
		static bool Register(RE::BSScript::IVirtualMachine* a_vm)
		{
			a_vm->BindNativeMethod(CLASS_NAME, "UpdateSettings", UpdateSettings);
			logger::info(FMT_STRING("Registered funcs for class {:s}"sv), CLASS_NAME);

			return true;
		}

	private:
		static constexpr char CLASS_NAME[] = "BakaFullscreenPipboy";

		static void UpdateSettings(std::monostate)
		{
			MCM::Settings::Update();
		}
	};
}
