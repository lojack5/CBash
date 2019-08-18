/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is CBash code.
 *
 * The Initial Developer of the Original Code is
 * Waruddar.
 * Portions created by the Initial Developer are Copyright (C) 2010
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */
#include "../../../Common.h"
#include "../IMODRecord.h"

namespace FNV
{
uint32_t IMODRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
    {
    switch(FieldID)
        {
        case 0: //recType
            return GetType();
        case 1: //flags1
            return UINT32_FLAG_FIELD;
        case 2: //fid
            return FORMID_FIELD;
        case 3: //versionControl1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 4: //eid
            return ISTRING_FIELD;
        case 5: //formVersion
            return UINT16_FIELD;
        case 6: //versionControl2
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 7: //boundX
            return SINT16_FIELD;
        case 8: //boundY
            return SINT16_FIELD;
        case 9: //boundZ
            return SINT16_FIELD;
        case 10: //full
            return STRING_FIELD;
        case 11: //modPath
            return ISTRING_FIELD;
        case 12: //modb
            return FLOAT32_FIELD;
        case 13: //modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MODL.IsLoaded() ? MODL->MODT.GetSize() : 0;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 14: //altTextures
            if(!MODL.IsLoaded())
                return UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)MODL->Textures.MODS.size();
                    default:
                        return UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= MODL->Textures.MODS.size())
                return UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //name
                    return STRING_FIELD;
                case 2: //texture
                    return FORMID_FIELD;
                case 3: //index
                    return SINT32_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }

        case 17: //modelFlags
            return UINT8_FIELD;
        case 18: //iconPath
            return ISTRING_FIELD;
        case 19: //smallIconPath
            return ISTRING_FIELD;
        case 20: //script
            return FORMID_FIELD;
        case 21: //description
            return STRING_FIELD;
        case 22: //dest Header
            return SINT32_FIELD;
        case 23: //dest Header
            return UINT8_FIELD;
        case 24: //dest Header
            return UINT8_FIELD;
        case 25: //dest_p Header
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 26: //dstd Destruction Stage Data
            return UINT8_FIELD;
        case 27: //dstd Destruction Stage Data
            return UINT8_FIELD;
        case 28: //dstd Destruction Stage Data
            return UINT8_FIELD;
        case 29: //dstd Destruction Stage Data
            return UINT8_FIELD;
        case 30: //dstd Destruction Stage Data
            return SINT32_FIELD;
        case 31: //dstd Destruction Stage Data
            return FORMID_FIELD;
        case 32: //dstd Destruction Stage Data
            return FORMID_FIELD;
        case 33: //dstd Destruction Stage Data
            return SINT32_FIELD;
        case 34: //dmdl Model Filename
            return ISTRING_FIELD;
        case 35: //dmdt_p Texture Files Hashes
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 0;
                    //return DMDT.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 36: //ynam Sound - Pick Up
            return FORMID_FIELD;
        case 37: //znam Sound - Drop
            return FORMID_FIELD;
        case 38: //data DATA ,, Struct
            return UINT32_FIELD;
        case 39: //data DATA ,, Struct
            return FLOAT32_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * IMODRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
    {
    switch(FieldID)
        {
        case 1: //flags1
            return &flags;
        case 2: //fid
            return &formID;
        case 3: //versionControl1
            *FieldValues = &flagsUnk;
            return NULL;
        case 4: //eid
            return EDID.value;
        case 5: //formVersion
            return &formVersion;
        case 6: //versionControl2
            *FieldValues = &versionControl2[0];
            return NULL;
        case 7: //boundX
            return OBND.IsLoaded() ? &OBND->x1 : NULL;
        case 8: //boundY
            return OBND.IsLoaded() ? &OBND->y1 : NULL;
        case 9: //boundZ
            return OBND.IsLoaded() ? &OBND->z1 : NULL;
        case 10: //full
            return FULL.value;
        case 11: //modPath
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 12: //modb
            return MODL.IsLoaded() ? &MODL->MODB.value : NULL;
        case 13: //modt_p
            *FieldValues = MODL.IsLoaded() ? MODL->MODT.value : NULL;
            return NULL;
        case 14: //mods Alternate Textures
            return NULL;
            //return MODL.IsLoaded() ? MODL->MODS.value : NULL;
        case 15: //mods Alternate Textures
            return NULL;
            //return MODL.IsLoaded() ? &MODL->MODS->value15 : NULL;
        case 16: //mods Alternate Textures
            return NULL;
            //return MODL.IsLoaded() ? &MODL->MODS->value16 : NULL;
        case 17: //modelFlags
            return MODL.IsLoaded() ? &MODL->MODD.value : NULL;
        case 18: //iconPath
            return ICON.value;
        case 19: //smallIconPath
            return MICO.value;
        case 20: //script
            return SCRI.IsLoaded() ? &SCRI.value : NULL;
        case 21: //description
            return DESC.value;
        case 22: //dest Header
            return Destructable.IsLoaded() ? &Destructable->DEST->health : NULL;
        case 23: //dest Header
            return Destructable.IsLoaded() ? &Destructable->DEST->count : NULL;
        case 24: //dest Header
            return Destructable.IsLoaded() ? &Destructable->DEST->flags : NULL;
        case 25: //dest_p Header
            *FieldValues = Destructable.IsLoaded() ? &Destructable->DEST->unused1[0] : NULL;
            return NULL;
        case 26: //dstd Destruction Stage Data
            // TODO: These need to be accessed as an array, not just the first DSTD
            return Destructable.IsLoaded() ? &Destructable->Stages.value[0]->DSTD->health : NULL;
        case 27: //dstd Destruction Stage Data
            return Destructable.IsLoaded() ? &Destructable->Stages.value[0]->DSTD->index : NULL;
        case 28: //dstd Destruction Stage Data
            return Destructable.IsLoaded() ? &Destructable->Stages.value[0]->DSTD->stage : NULL;
        case 29: //dstd Destruction Stage Data
            return Destructable.IsLoaded() ? &Destructable->Stages.value[0]->DSTD->flags : NULL;
        case 30: //dstd Destruction Stage Data
            return Destructable.IsLoaded() ? &Destructable->Stages.value[0]->DSTD->dps : NULL;
        case 31: //dstd Destruction Stage Data
            return Destructable.IsLoaded() ? &Destructable->Stages.value[0]->DSTD->explosion : NULL;
        case 32: //dstd Destruction Stage Data
            return Destructable.IsLoaded() ? &Destructable->Stages.value[0]->DSTD->debris : NULL;
        case 33: //dstd Destruction Stage Data
            return Destructable.IsLoaded() ? &Destructable->Stages.value[0]->DSTD->debrisCount : NULL;
        case 34: //dmdl Model Filename
            return Destructable.IsLoaded() ? Destructable->Stages.value[0]->DMDL.value : NULL;
        case 35: //dmdt_p Texture Files Hashes
            *FieldValues = (Destructable.IsLoaded()) ? Destructable->Stages.value[0]->DMDT.value : NULL;
            return NULL;
        case 36: //ynam Sound - Pick Up
            return YNAM.IsLoaded() ? &YNAM.value : NULL;
        case 37: //znam Sound - Drop
            return ZNAM.IsLoaded() ? &ZNAM.value : NULL;
        case 38: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value : NULL;
        case 39: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->weight : NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool IMODRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(*(uint32_t *)FieldValue);
            break;
        case 3: //versionControl1
            if(ArraySize != 4)
                break;
            ((UINT8ARRAY)&flagsUnk)[0] = ((UINT8ARRAY)FieldValue)[0];
            ((UINT8ARRAY)&flagsUnk)[1] = ((UINT8ARRAY)FieldValue)[1];
            ((UINT8ARRAY)&flagsUnk)[2] = ((UINT8ARRAY)FieldValue)[2];
            ((UINT8ARRAY)&flagsUnk)[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 4: //eid
            EDID.Copy((char *)FieldValue);
            break;
        case 5: //formVersion
            formVersion = *(uint16_t *)FieldValue;
            break;
        case 6: //versionControl2
            if(ArraySize != 2)
                break;
            versionControl2[0] = ((UINT8ARRAY)FieldValue)[0];
            versionControl2[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 7: //boundX
            OBND.Load();
            OBND->x1 = *(int16_t *)FieldValue;
            break;
        case 8: //boundY
            OBND.Load();
            OBND->y1 = *(int16_t *)FieldValue;
            break;
        case 9: //boundZ
            OBND.Load();
            OBND->z1 = *(int16_t *)FieldValue;
            break;
        case 10: //full
            FULL.Copy((char *)FieldValue);
            break;
        case 11: //modPath
            MODL.Load();
            MODL->MODL.Copy((char *)FieldValue);
            break;
        case 12: //modb
            MODL.Load();
            MODL->MODB.value = *(float *)FieldValue;
            break;
        case 13: //modt_p
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 14: //mods Alternate Textures
            MODL.Load();
            //MODL->Textures.MODS.Copy((char *)FieldValue);
            break;
        case 15: //mods Alternate Textures
            MODL.Load();
            MODL->Textures.Load();
            //MODL->Textres.MODS->value15 = *(FORMID *)FieldValue;
            return true;
        case 16: //mods Alternate Textures
            MODL.Load();
            MODL->Textures.Load();
            //MODL->Textures.MODS->value16 = *(int32_t *)FieldValue;
            break;
        case 17: //modelFlags
            MODL.Load();
            MODL->MODD.Load();
            MODL->MODD.value = *(uint8_t *)FieldValue;
            break;
        case 18: //iconPath
            ICON.Copy((char *)FieldValue);
            break;
        case 19: //smallIconPath
            MICO.Copy((char *)FieldValue);
            break;
        case 20: //script
            SCRI.Load();
            SCRI.value = *(FORMID *)FieldValue;
            return true;
        case 21: //description
            DESC.Copy((char *)FieldValue);
            break;
        case 22: //dest Header
            Destructable.Load();
            Destructable->DEST.Load();
            Destructable->DEST->health = *(int32_t *)FieldValue;
            break;
        case 23: //dest Header
            Destructable.Load();
            Destructable->DEST.Load();
            Destructable->DEST->count = *(uint8_t *)FieldValue;
            break;
        case 24: //dest Header
            Destructable.Load();
            Destructable->DEST.Load();
            Destructable->DEST->flags = *(uint8_t *)FieldValue;
            break;
        case 25: //dest_p Header
            if(ArraySize != 2)
                break;
            Destructable.Load();
            Destructable->DEST.Load();
            Destructable->DEST->unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            Destructable->DEST->unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 26: //dstd Destruction Stage Data
            // TODO Make the work on more than just the first destruction Stage item
            Destructable.Load();
            Destructable->Stages.value[0]->DSTD.Load();
            Destructable->Stages.value[0]->DSTD->health = *(uint8_t *)FieldValue;
            break;
        case 27: //dstd Destruction Stage Data
            Destructable.Load();
            Destructable->Stages.value[0]->DSTD.Load();
            Destructable->Stages.value[0]->DSTD->index = *(uint8_t *)FieldValue;
            break;
        case 28: //dstd Destruction Stage Data
            Destructable.Load();
            Destructable->Stages.value[0]->DSTD.Load();
            Destructable->Stages.value[0]->DSTD->stage = *(uint8_t *)FieldValue;
            break;
        case 29: //dstd Destruction Stage Data
            Destructable.Load();
            Destructable->Stages.value[0]->DSTD.Load();
            Destructable->Stages.value[0]->DSTD->flags = *(uint8_t *)FieldValue;
            break;
        case 30: //dstd Destruction Stage Data
            Destructable.Load();
            Destructable->Stages.value[0]->DSTD.Load();
            Destructable->Stages.value[0]->DSTD->dps = *(int32_t *)FieldValue;
            break;
        case 31: //dstd Destruction Stage Data
            Destructable.Load();
            Destructable->Stages.value[0]->DSTD.Load();
            Destructable->Stages.value[0]->DSTD->explosion = *(FORMID *)FieldValue;
            return true;
        case 32: //dstd Destruction Stage Data
            Destructable.Load();
            Destructable->Stages.value[0]->DSTD.Load();
            Destructable->Stages.value[0]->DSTD->debris = *(FORMID *)FieldValue;
            return true;
        case 33: //dstd Destruction Stage Data
            Destructable.Load();
            Destructable->Stages.value[0]->DSTD.Load();
            Destructable->Stages.value[0]->DSTD->debrisCount = *(int32_t *)FieldValue;
            break;
        case 34: //dmdl Model Filename
            Destructable.Load();
            Destructable->Stages.value[0]->DMDL.Copy((char *)FieldValue);
            break;
        case 35: //dmdt_p Texture Files Hashes
            Destructable.Load();
            Destructable->Stages.value[0]->DMDT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 36: //ynam Sound - Pick Up
            YNAM.Load();
            YNAM.value = *(FORMID *)FieldValue;
            return true;
        case 37: //znam Sound - Drop
            ZNAM.Load();
            ZNAM.value = *(FORMID *)FieldValue;
            return true;
        case 38: //data DATA ,, Struct
            DATA.Load();
            DATA->value = *(uint32_t *)FieldValue;
            break;
        case 39: //data DATA ,, Struct
            DATA.Load();
            DATA->weight = *(float *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void IMODRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(0);
            return;
        case 3: //versionControl1
            flagsUnk = 0;
            return;
        case 4: //eid
            EDID.Unload();
            return;
        case 5: //formVersion
            formVersion = 0;
            return;
        case 6: //versionControl2
            versionControl2[0] = 0;
            versionControl2[1] = 0;
            return;
        case 7: //boundX
            if (OBND.IsLoaded())
                OBND->x1 = 0; // defaultOBND.x;
            return;
        case 8: //boundY
            if (OBND.IsLoaded())
                OBND->y1 = 0; // defaultOBND.y;
            return;
        case 9: //boundZ
            if (OBND.IsLoaded())
                OBND->z1 = 0; // defaultOBND.z;
            return;
        case 10: //full
            FULL.Unload();
            return;
        case 11: //modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 12: //modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            return;
        case 13: //modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 14: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->Textures.Unload();
            return;
        case 15: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->Textures.Unload();
            return;
        case 16: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->Textures.Unload();
            return;
        case 17: //modelFlags
            if(MODL.IsLoaded())
                MODL->MODD.Unload();
            return;
        case 18: //iconPath
            ICON.Unload();
            return;
        case 19: //smallIconPath
            MICO.Unload();
            return;
        case 20: //script
            SCRI.Unload();
            return;
        case 21: //description
            DESC.Unload();
            return;
        case 22: //dest Header
            if(Destructable.IsLoaded())
                Destructable->DEST.Unload();
            return;
        case 23: //dest Header
            if(Destructable.IsLoaded())
                Destructable->DEST.Unload();
            return;
        case 24: //dest Header
            if(Destructable.IsLoaded())
                Destructable->DEST.Unload();
            return;
        case 25: //dest_p Header
            if(Destructable.IsLoaded())
                Destructable->DEST.Unload();
            return;
        case 26: //dstd Destruction Stage Data
            // TODO: Make this work on all stages
            if(Destructable.IsLoaded())
                Destructable->Stages.value[0]->DSTD.Unload();
            return;
        case 27: //dstd Destruction Stage Data
            if(Destructable.IsLoaded())
                Destructable->Stages.value[0]->DSTD.Unload();
            return;
        case 28: //dstd Destruction Stage Data
            if(Destructable.IsLoaded())
                Destructable->Stages.value[0]->DSTD.Unload();
            return;
        case 29: //dstd Destruction Stage Data
            if(Destructable.IsLoaded())
                Destructable->Stages.value[0]->DSTD.Unload();
            return;
        case 30: //dstd Destruction Stage Data
            if(Destructable.IsLoaded())
                Destructable->Stages.value[0]->DSTD.Unload();
            return;
        case 31: //dstd Destruction Stage Data
            if(Destructable.IsLoaded())
                Destructable->Stages.value[0]->DSTD.Unload();
            return;
        case 32: //dstd Destruction Stage Data
            if(Destructable.IsLoaded())
                Destructable->Stages.value[0]->DSTD.Unload();
            return;
        case 33: //dstd Destruction Stage Data
            if(Destructable.IsLoaded())
                Destructable->Stages.value[0]->DSTD.Unload();
            return;
        case 34: //dmdl Model Filename
            if(Destructable.IsLoaded())
                Destructable->Stages.value[0]->DMDL.Unload();
            return;
        case 35: //dmdt_p Texture Files Hashes
            if(Destructable.IsLoaded())
                Destructable->Stages.value[0]->DMDT.Unload();
            return;
        case 36: //ynam Sound - Pick Up
            YNAM.Unload();
            return;
        case 37: //znam Sound - Drop
            ZNAM.Unload();
            return;
        case 38: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 39: //data DATA ,, Struct
            DATA.Unload();
            return;
        default:
            return;
        }
    }
}