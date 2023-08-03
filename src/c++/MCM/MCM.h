#pragma once

namespace MCM
{
	class Settings
	{
	public:
		class Pipboy
		{
		public:
			inline static bool bEnable{ true };
			inline static bool bDisableFX{ true };
			inline static bool bUseColor{ true };
			inline static bool bUseColorPA{ true };
			inline static bool bBackground{ false };

			inline static double fPipboyViewportLeft{ 0.0 };
			inline static double fPipboyViewportRight{ 1.0 };
			inline static double fPipboyViewportTop{ 0.0 };
			inline static double fPipboyViewportBottom{ 0.92 };
			inline static double fTerminalViewportLeft{ 0.18 };
			inline static double fTerminalViewportRight{ 0.82 };
			inline static double fTerminalViewportTop{ 0.0 };
			inline static double fTerminalViewportBottom{ 0.92 };
		};

		static void Update()
		{
			if (m_FirstRun)
			{
				m_FirstRun = false;
			}

			if (auto UI = RE::UI::GetSingleton())
			{
				if (UI->GetMenuOpen("PipboyMenu"sv))
				{
					if (auto UIMessageQueue = RE::UIMessageQueue::GetSingleton())
					{
						UIMessageQueue->AddMessage("PipboyMenu"sv, RE::UI_MESSAGE_TYPE::kHide);
					}
				}
			}

			if (auto Renderer = RE::Interface3D::Renderer::GetByName("PipboyScreenModel"sv))
			{
				Renderer->Disable();
				Renderer->Release();
			}

			m_ini_base.LoadFile("Data/MCM/Config/BakaFullscreenPipboy/settings.ini");
			m_ini_user.LoadFile("Data/MCM/Settings/BakaFullscreenPipboy.ini");

			// Pipboy
			GetModSettingBool("Pipboy", "bEnable", Pipboy::bEnable);
			GetModSettingBool("Pipboy", "bDisableFX", Pipboy::bDisableFX);
			GetModSettingBool("Pipboy", "bUseColor", Pipboy::bUseColor);
			GetModSettingBool("Pipboy", "bUseColorPA", Pipboy::bUseColorPA);
			GetModSettingBool("Pipboy", "bBackground", Pipboy::bBackground);

			GetModSettingDouble("Pipboy", "fPipboyViewportLeft", Pipboy::fPipboyViewportLeft);
			GetModSettingDouble("Pipboy", "fPipboyViewportRight", Pipboy::fPipboyViewportRight);
			GetModSettingDouble("Pipboy", "fPipboyViewportTop", Pipboy::fPipboyViewportTop);
			GetModSettingDouble("Pipboy", "fPipboyViewportBottom", Pipboy::fPipboyViewportBottom);
			GetModSettingDouble("Pipboy", "fTerminalViewportLeft", Pipboy::fTerminalViewportLeft);
			GetModSettingDouble("Pipboy", "fTerminalViewportRight", Pipboy::fTerminalViewportRight);
			GetModSettingDouble("Pipboy", "fTerminalViewportTop", Pipboy::fTerminalViewportTop);
			GetModSettingDouble("Pipboy", "fTerminalViewportBottom", Pipboy::fTerminalViewportBottom);

			if (auto BakaPipboyNoAnims = RE::TESForm::GetFormByEditorID<RE::TESGlobal>("BakaPipboyNoAnims"))
			{
				BakaPipboyNoAnims->value = Pipboy::bEnable;
			}

			m_ini_base.Reset();
			m_ini_user.Reset();
		}

		inline static bool m_FirstRun{ true };

	private:
		static void GetModSettingChar(const std::string& a_section, const std::string& a_setting, std::string_view& a_value)
		{
			auto base = m_ini_base.GetValue(a_section.c_str(), a_setting.c_str(), a_value.data());
			auto user = m_ini_user.GetValue(a_section.c_str(), a_setting.c_str(), base);
			a_value = user;
		}

		static void GetModSettingBool(const std::string& a_section, const std::string& a_setting, bool& a_value)
		{
			auto base = m_ini_base.GetBoolValue(a_section.c_str(), a_setting.c_str(), a_value);
			auto user = m_ini_user.GetBoolValue(a_section.c_str(), a_setting.c_str(), base);
			a_value = user;
		}

		static void GetModSettingLong(const std::string& a_section, const std::string& a_setting, std::int32_t& a_value)
		{
			auto base = m_ini_base.GetLongValue(a_section.c_str(), a_setting.c_str(), a_value);
			auto user = m_ini_user.GetLongValue(a_section.c_str(), a_setting.c_str(), base);
			a_value = static_cast<std::int32_t>(user);
		}

		static void GetModSettingDouble(const std::string& a_section, const std::string& a_setting, double& a_value)
		{
			auto base = m_ini_base.GetDoubleValue(a_section.c_str(), a_setting.c_str(), a_value);
			auto user = m_ini_user.GetDoubleValue(a_section.c_str(), a_setting.c_str(), base);
			a_value = user;
		}

		inline static CSimpleIniA m_ini_base{ true };
		inline static CSimpleIniA m_ini_user{ true };
	};
}
