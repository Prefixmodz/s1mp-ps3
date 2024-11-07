#include "stdafx.h"

#pragma diag_suppress 77
SYS_MODULE_INFO(s1mp, 0, 1, 1);
SYS_MODULE_START(s1mp_start);
SYS_MODULE_STOP(s1mp_stop);

variables* g_vars;

//ScreenPlacement* scrPlaceView = reinterpret_cast<ScreenPlacement*>(static_cast<int>(game_table::scrplaceview));
//UiContext* cgDc = reinterpret_cast<UiContext*>(static_cast<int>(game_table::uicontext));

detour* r_endframe;
detour* sys_io_cellpadgetdata;

void R_EndFrame()
{
	g_change_overtime.update();

	g_menu->on_run();
	g_menu->on_draw();

	r_endframe->invoke<void>();
}

int sys_io_cellPadGetData(unsigned int port, CellPadData* data)
{
	if (port != 0)
		return sys_io_cellpadgetdata->invoke<int>(port, data);

	int returnValue = sys_io_cellpadgetdata->invoke<int>(port, g_input.GetInputData());
	std::memcpy(data, g_input.GetInputData(), sizeof(CellPadData));

	if (g_menu->is_open())
	{
		// Clear button flags
		data->button[CELL_PAD_BTN_OFFSET_DIGITAL1] &= ~(CELL_PAD_CTRL_LEFT | CELL_PAD_CTRL_DOWN | CELL_PAD_CTRL_RIGHT | CELL_PAD_CTRL_UP);
		data->button[CELL_PAD_BTN_OFFSET_DIGITAL2] &= ~(CELL_PAD_CTRL_CROSS | CELL_PAD_CTRL_CIRCLE);

		//if (g_Menu.IsMoving())
		//{
		//	// Clear analog values
		//	data->button[CELL_PAD_BTN_OFFSET_ANALOG_RIGHT_X] = 128;
		//	data->button[CELL_PAD_BTN_OFFSET_ANALOG_RIGHT_Y] = 128;
		//}
	}

	return returnValue;
}

int HenCheck(void) // returns 0x1337 if the console is hen
{
	system_call_1(8, 0x1337);
	return_to_user_prog(int);
}

extern "C" int s1mp_start(void)
{
	printf("Menu Loaded \n");
	*(int*)0x1D9768 = 0x48000240; // enable fps for hook to work

	set(0x6B0E20, 0x00000000); // fps text off

	g_input = CInput();
	g_vars = new variables();

	if (g_vars == nullptr)
		return SYS_PRX_STOP_FAILED;

	g_menu = new menu("CrEaTiiOnBrotherhood");

	if (g_menu == nullptr)
		return SYS_PRX_STOP_FAILED;

	memset(g_menu, 0, sizeof(menu));

	g_menu->on_build();
        if(HenCheck() == 0x1337)
	{
          detour::force_stub_address(0x674C79);
	  r_endframe = new detour(static_cast<int>(game_table::r_endframe), R_EndFrame);
	  sys_io_cellpadgetdata = new detour(static_cast<int>(game_table::sys_io_cellpadgetdata), sys_io_cellPadGetData);
	}
        else
	{
          r_endframe = new detour(static_cast<int>(game_table::r_endframe), R_EndFrame);
	  sys_io_cellpadgetdata = new detour(static_cast<int>(game_table::sys_io_cellpadgetdata), sys_io_cellPadGetData);
	}

	return SYS_PRX_START_OK;
}

extern "C" int s1mp_stop(void)
{
	memset(g_vars, 0, sizeof(variables));
	memset(g_menu, 0, sizeof(menu));
	printf("Menu Unloaded \n");
	delete	g_vars;
	delete g_menu;

	r_endframe->~detour();
	sys_io_cellpadgetdata->~detour();

	return SYS_PRX_STOP_OK;
}
