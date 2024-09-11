#pragma once

enum class game_table
{
    // AW
 /*   r_endframe = 0x5FD304,
    sys_io_cellpadgetdata = 0x779CE8,

    scrplaceview = 0xE1C940,
    uicontext = 0x269AA50,

    r_addcmddrawstretchpic = 0x5FAD38,
    cg_drawrotatedpicphysical = 0x1B2CB0,
    r_addcmddrawtext = 0x5FB4FC,
    db_findxassetheader = 0x2B5F80,
    r_textwidth = 0x5E2EC8,

    va = 0x4F50FC*/

    // W@W
    r_endframe = 0x01D8B88, // (fps hook)
    sys_io_cellpadgetdata = 0x649A94,

   /* scrplaceview = ,
    uicontext = ,*/

    r_addcmddrawstretchpic = 0x587A18,
    r_addcmddrawtext = 0x587588,
    material_registerhandle = 0x57C840,
    r_registerfont = 0x569278,
    //db_findxassetheader = ,
    r_textwidth = 0x569450,

    va = 0x3C7CB0
};