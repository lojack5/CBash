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
#include "../SCOLRecord.h"

namespace FNV
{
uint32_t SCOLRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 7: //boundX1
            return SINT16_FIELD;
        case 8: //boundY1
            return SINT16_FIELD;
        case 9: //boundZ1
            return SINT16_FIELD;
        case 10: //boundX2
            return SINT16_FIELD;
        case 11: //boundY2
            return SINT16_FIELD;
        case 12: //boundZ2
            return SINT16_FIELD;
        case 13: //modPath
            return ISTRING_FIELD;
        case 14: //modb
            return FLOAT32_FIELD;
        case 15: //modt_p
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
        case 16: //altTextures
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
            return UNKNOWN_FIELD;
        case 17: //modelFlags
            return UINT8_FLAG_FIELD;
        case 18: //statics
            if(ListFieldID == 0) //statics
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)Parts.value.size();
                    default:
                        return UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= Parts.value.size())
                return UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //static
                    return FORMID_FIELD;
                case 2: //placements
                    if(ListX2FieldID == 0) //placements
                        {
                        switch(WhichAttribute)
                            {
                            case 0: //fieldType
                                return LIST_FIELD;
                            case 1: //fieldSize
                                return (uint32_t)Parts.value[ListIndex]->DATA.value.size();
                            default:
                                return UNKNOWN_FIELD;
                            }
                        }

                    if(ListX2Index >= Parts.value[ListIndex]->DATA.value.size())
                        return UNKNOWN_FIELD;

                    switch(ListX2FieldID)
                        {
                        case 1: //posX
                            return FLOAT32_FIELD;
                        case 2: //posY
                            return FLOAT32_FIELD;
                        case 3: //posZ
                            return FLOAT32_FIELD;
                        case 4: //rotX
                            return RADIAN_FIELD;
                        case 5: //rotY
                            return RADIAN_FIELD;
                        case 6: //rotZ
                            return RADIAN_FIELD;
                        case 7: //scale
                            return FLOAT32_FIELD;
                        default:
                            return UNKNOWN_FIELD;
                        }
                    return UNKNOWN_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * SCOLRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //boundX1
            return &OBND.value.x1;
        case 8: //boundY1
            return &OBND.value.y1;
        case 9: //boundZ1
            return &OBND.value.z1;
        case 10: //boundX2
            return &OBND.value.x2;
        case 11: //boundY2
            return &OBND.value.y2;
        case 12: //boundZ2
            return &OBND.value.z2;
        case 13: //modPath
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 14: //modb
            return MODL.IsLoaded() ? &MODL->MODB.value : NULL;
        case 15: //modt_p
            *FieldValues = MODL.IsLoaded() ? MODL->MODT.value : NULL;
            return NULL;
        case 16: //altTextures
            if(!MODL.IsLoaded())
                return NULL;

            if(ListIndex >= MODL->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return MODL->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &MODL->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &MODL->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 17: //modelFlags
            return MODL.IsLoaded() ? &MODL->MODD.value : NULL;
        case 18: //statics
            if(ListIndex >= Parts.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //static
                    return &Parts.value[ListIndex]->ONAM.value;
                case 2: //placements
                    if(ListX2Index >= Parts.value[ListIndex]->DATA.value.size())
                        return NULL;

                    switch(ListX2FieldID)
                        {
                        case 1: //posX
                            return &Parts.value[ListIndex]->DATA.value[ListX2Index].posX;
                        case 2: //posY
                            return &Parts.value[ListIndex]->DATA.value[ListX2Index].posY;
                        case 3: //posZ
                            return &Parts.value[ListIndex]->DATA.value[ListX2Index].posZ;
                        case 4: //rotX
                            return &Parts.value[ListIndex]->DATA.value[ListX2Index].rotX;
                        case 5: //rotY
                            return &Parts.value[ListIndex]->DATA.value[ListX2Index].rotY;
                        case 6: //rotZ
                            return &Parts.value[ListIndex]->DATA.value[ListX2Index].rotZ;
                        case 7: //scale
                            return &Parts.value[ListIndex]->DATA.value[ListX2Index].scale;
                        default:
                            return NULL;
                        }
                    return NULL;
                default:
                    return NULL;
                }
            return NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool SCOLRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 7: //boundX1
            OBND.value.x1 = *(int16_t *)FieldValue;
            break;
        case 8: //boundY1
            OBND.value.y1 = *(int16_t *)FieldValue;
            break;
        case 9: //boundZ1
            OBND.value.z1 = *(int16_t *)FieldValue;
            break;
        case 10: //boundX2
            OBND.value.x2 = *(int16_t *)FieldValue;
            break;
        case 11: //boundY2
            OBND.value.y2 = *(int16_t *)FieldValue;
            break;
        case 12: //boundZ2
            OBND.value.z2 = *(int16_t *)FieldValue;
            break;
        case 13: //modPath
            MODL.Load();
            MODL->MODL.Copy((char *)FieldValue);
            break;
        case 14: //modb
            MODL.Load();
            MODL->MODB.value = *(float *)FieldValue;
            break;
        case 15: //modt_p
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 16: //altTextures
            MODL.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                MODL->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= MODL->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []MODL->Textures.MODS[ListIndex]->name;
                    MODL->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        MODL->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strncpy(MODL->Textures.MODS[ListIndex]->name, (char *)FieldValue, ArraySize);
                        }
                    break;
                case 2: //texture
                    MODL->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    MODL->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 17: //modelFlags
            MODL.Load();
            MODL->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 18: //statics
            if(ListFieldID == 0) //staticsSize
                {
                Parts.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Parts.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //static
                    Parts.value[ListIndex]->ONAM.value = *(FORMID *)FieldValue;
                    return true;
                case 2: //placements
                    if(ListX2FieldID == 0) //staticsSize
                        {
                        Parts.value[ListIndex]->DATA.resize(ArraySize);
                        return false;
                        }

                    if(ListX2Index >= Parts.value[ListIndex]->DATA.value.size())
                        break;

                    switch(ListX2FieldID)
                        {
                        case 1: //posX
                            Parts.value[ListIndex]->DATA.value[ListX2Index].posX = *(float *)FieldValue;
                            break;
                        case 2: //posY
                            Parts.value[ListIndex]->DATA.value[ListX2Index].posY = *(float *)FieldValue;
                            break;
                        case 3: //posZ
                            Parts.value[ListIndex]->DATA.value[ListX2Index].posZ = *(float *)FieldValue;
                            break;
                        case 4: //rotX
                            Parts.value[ListIndex]->DATA.value[ListX2Index].rotX = *(float *)FieldValue;
                            break;
                        case 5: //rotY
                            Parts.value[ListIndex]->DATA.value[ListX2Index].rotY = *(float *)FieldValue;
                            break;
                        case 6: //rotZ
                            Parts.value[ListIndex]->DATA.value[ListX2Index].rotZ = *(float *)FieldValue;
                            break;
                        case 7: //scale
                            Parts.value[ListIndex]->DATA.value[ListX2Index].scale = *(float *)FieldValue;
                            break;
                        default:
                            break;
                        }
                    break;
                default:
                    break;
                }
            break;
        default:
            break;
        }
    return false;
    }

void SCOLRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    GENOBND defaultOBND;
    FNVMODS defaultMODS;
    SCOLDATA defaultDATA;
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
        case 7: //boundX1
            OBND.value.x1 = defaultOBND.x1;
            return;
        case 8: //boundY1
            OBND.value.y1 = defaultOBND.y1;
            return;
        case 9: //boundZ1
            OBND.value.z1 = defaultOBND.z1;
            return;
        case 10: //boundX2
            OBND.value.x2 = defaultOBND.x2;
            return;
        case 11: //boundY2
            OBND.value.y2 = defaultOBND.y2;
            return;
        case 12: //boundZ2
            OBND.value.z2 = defaultOBND.z2;
            return;
        case 13: //modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 14: //modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            return;
        case 15: //modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 16: //altTextures
            if(MODL.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    MODL->Textures.Unload();
                    return;
                    }

                if(ListIndex >= MODL->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []MODL->Textures.MODS[ListIndex]->name;
                        MODL->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        MODL->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        MODL->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 17: //modelFlags
            if(MODL.IsLoaded())
                MODL->MODD.Unload();
            return;
        case 18: //statics
            if(ListFieldID == 0) //staticsSize
                {
                Parts.Unload();
                return;
                }

            if(ListIndex >= Parts.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //static
                    Parts.value[ListIndex]->ONAM.Unload();
                    return;
                case 2: //placements
                    if(ListX2FieldID == 0) //staticsSize
                        {
                        Parts.value[ListIndex]->DATA.Unload();
                        return;
                        }

                    if(ListX2Index >= Parts.value[ListIndex]->DATA.value.size())
                        return;

                    switch(ListX2FieldID)
                        {
                        case 1: //posX
                            Parts.value[ListIndex]->DATA.value[ListX2Index].posX = defaultDATA.posX;
                            return;
                        case 2: //posY
                            Parts.value[ListIndex]->DATA.value[ListX2Index].posY = defaultDATA.posY;
                            return;
                        case 3: //posZ
                            Parts.value[ListIndex]->DATA.value[ListX2Index].posZ = defaultDATA.posZ;
                            return;
                        case 4: //rotX
                            Parts.value[ListIndex]->DATA.value[ListX2Index].rotX = defaultDATA.rotX;
                            return;
                        case 5: //rotY
                            Parts.value[ListIndex]->DATA.value[ListX2Index].rotY = defaultDATA.rotY;
                            return;
                        case 6: //rotZ
                            Parts.value[ListIndex]->DATA.value[ListX2Index].rotZ = defaultDATA.rotZ;
                            return;
                        case 7: //scale
                            Parts.value[ListIndex]->DATA.value[ListX2Index].scale = defaultDATA.scale;
                            return;
                        default:
                            return;
                        }
                    return;
                default:
                    return;
                }
            return;
        default:
            return;
        }
    return;
    }
}