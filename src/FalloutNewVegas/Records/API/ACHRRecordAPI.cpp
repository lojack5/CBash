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
#include "../ACHRRecord.h"

namespace FNV
{
uint32_t ACHRRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 7: //base
            return FORMID_FIELD;
        case 8: //encounterZone
            return FORMID_FIELD;
        case 9: //xrgd_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XRGD.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 10: //xrgb_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XRGB.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 11: //idleTime
            return FLOAT32_FIELD;
        case 12: //idle
            return FORMID_FIELD;
        case 13: //unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return Patrol.IsLoaded() ? 4 : 0;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 14: //numRefs
            return UINT32_FIELD;
        case 15: //compiledSize
            return UINT32_FIELD;
        case 16: //lastIndex
            return UINT32_FIELD;
        case 17: //scriptType
            return UINT16_TYPE_FIELD;
        case 18: //scriptFlags
            return UINT16_FLAG_FIELD;
        case 19: //compiled_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return Patrol.IsLoaded() ? Patrol->SCDA.GetSize() : 0;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 20: //scriptText
            return ISTRING_FIELD;
        case 21: //vars
            if(!Patrol.IsLoaded())
                return UNKNOWN_FIELD;

            if(ListFieldID == 0) //vars
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)Patrol->VARS.value.size();
                    default:
                        return UNKNOWN_FIELD;
                    }
                return UNKNOWN_FIELD;
                }

            if(ListIndex >= Patrol->VARS.value.size())
                return UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //index
                    return UINT32_FIELD;
                case 2: //unused1
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            return 12;
                        default:
                            return UNKNOWN_FIELD;
                        }
                    return UNKNOWN_FIELD;
                case 3: //flags
                    return UINT8_FLAG_FIELD;
                case 4: //unused2
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            return 7;
                        default:
                            return UNKNOWN_FIELD;
                        }
                    return UNKNOWN_FIELD;
                case 5: //name
                    return ISTRING_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 22: //references
            if(!Patrol.IsLoaded())
                return UNKNOWN_FIELD;

            if(ListFieldID == 0) //references
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return FORMID_OR_UINT32_ARRAY_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)Patrol->SCR_.value.size();
                    default:
                        return UNKNOWN_FIELD;
                    }
                return UNKNOWN_FIELD;
                }

            if(ListIndex >= Patrol->SCR_.value.size())
                return UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //reference
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return FORMID_OR_UINT32_FIELD;
                        case 2: //WhichType
                            return Patrol->SCR_.value[ListIndex]->isSCRO ? FORMID_FIELD : UINT32_FIELD;
                        default:
                            return UNKNOWN_FIELD;
                        }
                    return UNKNOWN_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 23: //topic
            return FORMID_FIELD;
        case 24: //levelMod
            return SINT32_FIELD;
        case 25: //merchantContainer
            return FORMID_FIELD;
        case 26: //count
            return SINT32_FIELD;
        case 27: //radius
            return FLOAT32_FIELD;
        case 28: //health
            return FLOAT32_FIELD;
        case 29: //decals
            if(ListFieldID == 0) //decals
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)XDCR.value.size();
                    default:
                        return UNKNOWN_FIELD;
                    }
                return UNKNOWN_FIELD;
                }

            if(ListIndex >= XDCR.value.size())
                return UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //reference
                    return FORMID_FIELD;
                case 2: //unknown1
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            return 24;
                        default:
                            return UNKNOWN_FIELD;
                        }
                    return UNKNOWN_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 30: //linkedReference
            return FORMID_FIELD;
        case 31: //startRed
            return UINT8_FIELD;
        case 32: //startGreen
            return UINT8_FIELD;
        case 33: //startBlue
            return UINT8_FIELD;
        case 34: //unused2
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XCLP.IsLoaded() ? 1 : 0;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 35: //endRed
            return UINT8_FIELD;
        case 36: //endGreen
            return UINT8_FIELD;
        case 37: //endBlue
            return UINT8_FIELD;
        case 38: //unused3
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XCLP.IsLoaded() ? 1 : 0;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 39: //activateParentFlags
            return UINT8_FLAG_FIELD;
        case 40: //activateParentRefs
            if(!ActivateParents.IsLoaded())
                return UNKNOWN_FIELD;

            if(ListFieldID == 0) //activateParentRefs
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)ActivateParents->XAPR.value.size();
                    default:
                        return UNKNOWN_FIELD;
                    }
                return UNKNOWN_FIELD;
                }

            if(ListIndex >= ActivateParents->XAPR.value.size())
                return UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //reference
                    return FORMID_FIELD;
                case 2: //delay
                    return FLOAT32_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 41: //prompt
            return STRING_FIELD;
        case 42: //parent
            return FORMID_FIELD;
        case 43: //parentFlags
            return UINT8_FLAG_FIELD;
        case 44: //unused4
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XESP.IsLoaded() ? 3 : 0;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 45: //emittance
            return FORMID_FIELD;
        case 46: //boundRef
            return FORMID_FIELD;
        case 47: //ignoredBySandbox
            return BOOL_FIELD;
        case 48: //scale
            return FLOAT32_FIELD;
        case 49: //posX
            return FLOAT32_FIELD;
        case 50: //posY
            return FLOAT32_FIELD;
        case 51: //posZ
            return FLOAT32_FIELD;
        case 52: //rotX
            return RADIAN_FIELD;
        case 53: //rotY
            return RADIAN_FIELD;
        case 54: //rotZ
            return RADIAN_FIELD;
        case 55: //Parent
            return PARENTRECORD_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * ACHRRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //base
            return &NAME.value;
        case 8: //encounterZone
            return &XEZN.value;
        case 9: //xrgd_p
            *FieldValues = XRGD.value;
            return NULL;
        case 10: //xrgb_p
            *FieldValues = XRGB.value;
            return NULL;
        case 11: //idleTime
            return Patrol.IsLoaded() ? &Patrol->XPRD.value : NULL;
        case 12: //idle
            return Patrol.IsLoaded() ? &Patrol->INAM.value : NULL;
        case 13: //unused1
            *FieldValues = Patrol.IsLoaded() ? &Patrol->SCHR.value.unused1[0] : NULL;
            return NULL;
        case 14: //numRefs
            return Patrol.IsLoaded() ? &Patrol->SCHR.value.numRefs : NULL;
        case 15: //compiledSize
            return Patrol.IsLoaded() ? &Patrol->SCHR.value.compiledSize : NULL;
        case 16: //lastIndex
            return Patrol.IsLoaded() ? &Patrol->SCHR.value.lastIndex : NULL;
        case 17: //scriptType
            return Patrol.IsLoaded() ? &Patrol->SCHR.value.scriptType : NULL;
        case 18: //scriptFlags
            return Patrol.IsLoaded() ? &Patrol->SCHR.value.flags : NULL;
        case 19: //compiled_p
            *FieldValues = Patrol.IsLoaded() ? Patrol->SCDA.value : NULL;
            return NULL;
        case 20: //scriptText
            return Patrol.IsLoaded() ? Patrol->SCTX.value : NULL;
        case 21: //vars
            if(!Patrol.IsLoaded())
                return NULL;

            if(ListIndex >= Patrol->VARS.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //index
                    return &Patrol->VARS.value[ListIndex]->SLSD.value.index;
                case 2: //unused1
                    *FieldValues = &Patrol->VARS.value[ListIndex]->SLSD.value.unused1[0];
                    return NULL;
                case 3: //flags
                    return &Patrol->VARS.value[ListIndex]->SLSD.value.flags;
                case 4: //unused2
                    *FieldValues = &Patrol->VARS.value[ListIndex]->SLSD.value.unused2[0];
                    return NULL;
                case 5: //name
                    return Patrol->VARS.value[ListIndex]->SCVR.value;
                default:
                    return NULL;
                }
            return NULL;
        case 22: //references
            if(!Patrol.IsLoaded())
                {
                *FieldValues = NULL;
                return NULL;
                }
            for(uint32_t x = 0; x < Patrol->SCR_.value.size(); ++x)
                ((FORMIDARRAY)FieldValues)[x] = Patrol->SCR_.value[x]->reference;
            return NULL;
        case 23: //topic
            return Patrol.IsLoaded() ? &Patrol->TNAM.value : NULL;
        case 24: //levelMod
            return &XLCM.value;
        case 25: //merchantContainer
            return &XMRC.value;
        case 26: //count
            return &XCNT.value;
        case 27: //radius
            return &XRDS.value;
        case 28: //health
            return &XHLP.value;
        case 29: //decals
            if(ListIndex >= XDCR.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //reference
                    return &XDCR.value[ListIndex]->reference;
                case 2: //unknown1
                    *FieldValues = &XDCR.value[ListIndex]->unknown1[0];
                    return NULL;
                default:
                    return NULL;
                }
            return NULL;
        case 30: //linkedReference
            return &XLKR.value;
        case 31: //startRed
            return XCLP.IsLoaded() ? &XCLP->start.red : NULL;
        case 32: //startGreen
            return XCLP.IsLoaded() ? &XCLP->start.green : NULL;
        case 33: //startBlue
            return XCLP.IsLoaded() ? &XCLP->start.blue : NULL;
        case 34: //unused2
            *FieldValues = XCLP.IsLoaded() ? &XCLP->start.unused1 : NULL;
            return NULL;
        case 35: //endRed
            return XCLP.IsLoaded() ? &XCLP->end.red : NULL;
        case 36: //endGreen
            return XCLP.IsLoaded() ? &XCLP->end.green : NULL;
        case 37: //endBlue
            return XCLP.IsLoaded() ? &XCLP->end.blue : NULL;
        case 38: //unused3
            *FieldValues = XCLP.IsLoaded() ? &XCLP->end.unused1 : NULL;
            return NULL;
        case 39: //activateParentFlags
            return ActivateParents.IsLoaded() ? &ActivateParents->XAPD.value : NULL;
        case 40: //activateParentRefs
            if(!ActivateParents.IsLoaded())
                return NULL;

            if(ListIndex >= ActivateParents->XAPR.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //reference
                    return &ActivateParents->XAPR.value[ListIndex]->reference;
                case 2: //delay
                    return &ActivateParents->XAPR.value[ListIndex]->delay;
                default:
                    return NULL;
                }
            return NULL;
        case 41: //prompt
            return XATO.value;
        case 42: //parent
            return XESP.IsLoaded() ? &XESP->parent : NULL;
        case 43: //parentFlags
            return XESP.IsLoaded() ? &XESP->flags : NULL;
        case 44: //unused4
            *FieldValues = XESP.IsLoaded() ? &XESP->unused1[0] : NULL;
            return NULL;
        case 45: //emittance
            return &XEMI.value;
        case 46: //boundRef
            return &XMBR.value;
        case 47: //ignoredBySandbox
            return &XIBS.value;
        case 48: //scale
            return &XSCL.value;
        case 49: //posX
            return &DATA.value.posX;
        case 50: //posY
            return &DATA.value.posY;
        case 51: //posZ
            return &DATA.value.posZ;
        case 52: //rotX
            return &DATA.value.rotX;
        case 53: //rotY
            return &DATA.value.rotY;
        case 54: //rotZ
            return &DATA.value.rotZ;
        case 55: //Parent
            return GetParentRecord();
        default:
            return NULL;
        }
    return NULL;
    }

bool ACHRRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 7: //base
            NAME.value = *(FORMID *)FieldValue;
            return true;
        case 8: //encounterZone
            XEZN.value = *(FORMID *)FieldValue;
            return true;
        case 9: //xrgd_p
            XRGD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 10: //xrgp_p
            XRGB.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 11: //idleTime
            Patrol.Load();
            Patrol->XPRD.value = *(float *)FieldValue;
            break;
        case 12: //idle
            Patrol.Load();
            Patrol->INAM.value = *(FORMID *)FieldValue;
            return true;
        case 13: //unused1
            if(ArraySize != 4)
                break;
            Patrol.Load();
            Patrol->SCHR.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            Patrol->SCHR.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            Patrol->SCHR.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            Patrol->SCHR.value.unused1[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 14: //numRefs
            Patrol.Load();
            Patrol->SCHR.value.numRefs = *(uint32_t *)FieldValue;
            break;
        case 15: //compiledSize
            Patrol.Load();
            Patrol->SCHR.value.compiledSize = *(uint32_t *)FieldValue;
            break;
        case 16: //lastIndex
            Patrol.Load();
            Patrol->SCHR.value.lastIndex = *(uint32_t *)FieldValue;
            break;
        case 17: //scriptType
            Patrol.Load();
            Patrol->SetType(*(uint16_t *)FieldValue);
            break;
        case 18: //scriptFlags
            Patrol.Load();
            Patrol->SetScriptFlagMask(*(uint16_t *)FieldValue);
            break;
        case 19: //compiled_p
            Patrol.Load();
            Patrol->SCDA.Copy((UINT8ARRAY)FieldValue, ArraySize);
            Patrol->SCHR.value.compiledSize = ArraySize;
            break;
        case 20: //scriptText
            Patrol.Load();
            Patrol->SCTX.Copy((char *)FieldValue);
            break;
        case 21: //VARS
            Patrol.Load();
            if(ListFieldID == 0) //VARSSize
                {
                Patrol->VARS.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Patrol->VARS.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //index
                    Patrol->VARS.value[ListIndex]->SLSD.value.index = *(uint32_t *)FieldValue;
                    break;
                case 2: //unused1
                    if(ArraySize != 12)
                        break;
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[3] = ((UINT8ARRAY)FieldValue)[3];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[4] = ((UINT8ARRAY)FieldValue)[4];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[5] = ((UINT8ARRAY)FieldValue)[5];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[6] = ((UINT8ARRAY)FieldValue)[6];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[7] = ((UINT8ARRAY)FieldValue)[7];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[8] = ((UINT8ARRAY)FieldValue)[8];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[9] = ((UINT8ARRAY)FieldValue)[9];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[10] = ((UINT8ARRAY)FieldValue)[10];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[11] = ((UINT8ARRAY)FieldValue)[11];
                    break;
                case 3: //flags
                    Patrol->VARS.value[ListIndex]->SetFlagMask(*(uint8_t *)FieldValue);
                    break;
                case 4: //unused2
                    if(ArraySize != 7)
                        break;
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[0] = ((UINT8ARRAY)FieldValue)[0];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[1] = ((UINT8ARRAY)FieldValue)[1];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[2] = ((UINT8ARRAY)FieldValue)[2];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[3] = ((UINT8ARRAY)FieldValue)[3];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[4] = ((UINT8ARRAY)FieldValue)[4];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[5] = ((UINT8ARRAY)FieldValue)[5];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[6] = ((UINT8ARRAY)FieldValue)[6];
                    break;
                case 5: //name
                    Patrol->VARS.value[ListIndex]->SCVR.Copy((char *)FieldValue);
                    break;
                default:
                    break;
                }
            break;
        case 22: //references
            Patrol.Load();
            if(ListFieldID == 0) //referencesSize
                {
                Patrol->SCR_.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Patrol->SCR_.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //reference
                    //Borrowing ArraySize to flag if the new value is a formID
                    Patrol->SCR_.value[ListIndex]->reference = *(uint32_t *)FieldValue;
                    Patrol->SCR_.value[ListIndex]->isSCRO = ArraySize ? true : false;
                    return ArraySize != 0;
                default:
                    break;
                }
            break;
        case 23: //topic
            Patrol.Load();
            Patrol->TNAM.value = *(FORMID *)FieldValue;
            return true;
        case 24: //levelMod
            XLCM.value = *(int32_t *)FieldValue;
            break;
        case 25: //merchantContainer
            XMRC.value = *(FORMID *)FieldValue;
            return true;
        case 26: //count
            XCNT.value = *(int32_t *)FieldValue;
            break;
        case 27: //radius
            XRDS.value = *(float *)FieldValue;
            break;
        case 28: //health
            XHLP.value = *(float *)FieldValue;
            break;
        case 29: //decals
            if(ListFieldID == 0) //decalsSize
                {
                XDCR.resize(ArraySize);
                return false;
                }

            if(ListIndex >= XDCR.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //reference
                    XDCR.value[ListIndex]->reference = *(FORMID *)FieldValue;
                    return true;
                case 2: //unknown1
                    if(ArraySize != 24)
                        break;
                    memcpy(&XDCR.value[ListIndex]->unknown1[0], FieldValue, sizeof(XDCR.value[ListIndex]->unknown1));
                    break;
                default:
                    break;
                }
            break;
        case 30: //linkedReference
            XLKR.value = *(FORMID *)FieldValue;
            return true;
        case 31: //startRed
            XCLP.Load();
            XCLP->start.red = *(uint8_t *)FieldValue;
            break;
        case 32: //startGreen
            XCLP.Load();
            XCLP->start.green = *(uint8_t *)FieldValue;
            break;
        case 33: //startBlue
            XCLP.Load();
            XCLP->start.blue = *(uint8_t *)FieldValue;
            break;
        case 34: //unused2
            if(ArraySize != 1)
                break;
            XCLP.Load();
            XCLP->start.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 35: //endRed
            XCLP.Load();
            XCLP->end.red = *(uint8_t *)FieldValue;
            break;
        case 36: //endGreen
            XCLP.Load();
            XCLP->end.green = *(uint8_t *)FieldValue;
            break;
        case 37: //endBlue
            XCLP.Load();
            XCLP->end.blue = *(uint8_t *)FieldValue;
            break;
        case 38: //unused3
            if(ArraySize != 1)
                break;
            XCLP.Load();
            XCLP->end.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 39: //activateParentFlags
            ActivateParents.Load();
            ActivateParents->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 40: //activateParentRefs
            ActivateParents.Load();
            if(ListFieldID == 0) //decalsSize
                {
                ActivateParents->XAPR.resize(ArraySize);
                return false;
                }

            if(ListIndex >= ActivateParents->XAPR.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //reference
                    ActivateParents->XAPR.value[ListIndex]->reference = *(FORMID *)FieldValue;
                    return true;
                case 2: //delay
                    ActivateParents->XAPR.value[ListIndex]->delay = *(float *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 41: //prompt
            XATO.Copy((char *)FieldValue);
            break;
        case 42: //parent
            XESP.Load();
            XESP->parent = *(FORMID *)FieldValue;
            return true;
        case 43: //parentFlags
            SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 44: //unused4
            if(ArraySize != 3)
                break;
            XESP.Load();
            XESP->unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            XESP->unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            XESP->unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 45: //emittance
            XEMI.value = *(FORMID *)FieldValue;
            return true;
        case 46: //boundRef
            XMBR.value = *(FORMID *)FieldValue;
            return true;
        case 47: //ignoredBySandbox
            XIBS.value = *(uint8_t *)FieldValue;
            break;
        case 48: //scale
            XSCL.value = *(float *)FieldValue;
            break;
        case 49: //posX
            DATA.value.posX = *(float *)FieldValue;
            break;
        case 50: //posY
            DATA.value.posY = *(float *)FieldValue;
            break;
        case 51: //posZ
            DATA.value.posZ = *(float *)FieldValue;
            break;
        case 52: //rotX
            DATA.value.rotX = *(float *)FieldValue;
            break;
        case 53: //rotY
            DATA.value.rotY = *(float *)FieldValue;
            break;
        case 54: //rotZ
            DATA.value.rotZ = *(float *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void ACHRRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    FNVSCHR defaultSCHR;

    GENVARS defaultVARS;
    GENSCR_ defaultSCR_;
    GENCLR defaultCLR;
    GENXDCR defaultXDCR;
    GENXAPR defaultXAPR;
    GENXESP defaultXESP;
    GENPOSDATA defaultDATA;
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
        case 7: //base
            NAME.Unload();
            return;
        case 8: //encounterZone
            XEZN.Unload();
            return;
        case 9: //xrgd_p
            XRGD.Unload();
            return;
        case 10: //xrgp_p
            XRGB.Unload();
            return;
        case 11: //idleTime
            if(Patrol.IsLoaded())
                Patrol->XPRD.Unload();
            return;
        case 12: //idle
            if(Patrol.IsLoaded())
                Patrol->INAM.Unload();
            return;
        case 13: //unused1
            if(Patrol.IsLoaded())
                {
                Patrol->SCHR.value.unused1[0] = defaultSCHR.unused1[0];
                Patrol->SCHR.value.unused1[1] = defaultSCHR.unused1[1];
                Patrol->SCHR.value.unused1[2] = defaultSCHR.unused1[2];
                Patrol->SCHR.value.unused1[3] = defaultSCHR.unused1[3];
                }
            return;
        case 14: //numRefs
            if(Patrol.IsLoaded())
                Patrol->SCHR.value.numRefs = defaultSCHR.numRefs;
            return;
        case 15: //compiledSize
            if(Patrol.IsLoaded())
                Patrol->SCHR.value.compiledSize = defaultSCHR.compiledSize;
            return;
        case 16: //lastIndex
            if(Patrol.IsLoaded())
                Patrol->SCHR.value.lastIndex = defaultSCHR.lastIndex;
            return;
        case 17: //scriptType
            if(Patrol.IsLoaded())
                Patrol->SetType(defaultSCHR.scriptType);
            return;
        case 18: //scriptFlags
            if(Patrol.IsLoaded())
                Patrol->SetScriptFlagMask(defaultSCHR.flags);
            return;
        case 19: //compiled_p
            if(Patrol.IsLoaded())
                Patrol->SCDA.Unload();
            return;
        case 20: //scriptText
            if(Patrol.IsLoaded())
                Patrol->SCTX.Unload();
            return;
        case 21: //VARS
            if(!Patrol.IsLoaded())
                return;
            if(ListFieldID == 0) //VARS
                {
                Patrol->VARS.Unload();
                return;
                }

            if(ListIndex >= Patrol->VARS.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //index
                    Patrol->VARS.value[ListIndex]->SLSD.value.index = defaultVARS.SLSD.value.index;
                    return;
                case 2: //unused1
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[0] = defaultVARS.SLSD.value.unused1[0];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[1] = defaultVARS.SLSD.value.unused1[1];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[2] = defaultVARS.SLSD.value.unused1[2];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[3] = defaultVARS.SLSD.value.unused1[3];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[4] = defaultVARS.SLSD.value.unused1[4];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[5] = defaultVARS.SLSD.value.unused1[5];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[6] = defaultVARS.SLSD.value.unused1[6];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[7] = defaultVARS.SLSD.value.unused1[7];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[8] = defaultVARS.SLSD.value.unused1[8];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[9] = defaultVARS.SLSD.value.unused1[9];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[10] = defaultVARS.SLSD.value.unused1[10];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[11] = defaultVARS.SLSD.value.unused1[11];
                    return;
                case 3: //flags
                    Patrol->VARS.value[ListIndex]->SLSD.value.flags = defaultVARS.SLSD.value.flags;
                    return;
                case 4: //unused2
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[0] = defaultVARS.SLSD.value.unused2[0];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[1] = defaultVARS.SLSD.value.unused2[1];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[2] = defaultVARS.SLSD.value.unused2[2];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[3] = defaultVARS.SLSD.value.unused2[3];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[4] = defaultVARS.SLSD.value.unused2[4];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[5] = defaultVARS.SLSD.value.unused2[5];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[6] = defaultVARS.SLSD.value.unused2[6];
                    return;
                case 5: //name
                    Patrol->VARS.value[ListIndex]->SCVR.Unload();
                    return;
                default:
                    return;
                }
            return;
        case 22: //references
            if(!Patrol.IsLoaded())
                return;

            if(ListFieldID == 0) //references
                {
                Patrol->SCR_.Unload();
                return;
                }

            if(ListIndex >= Patrol->SCR_.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //reference
                    Patrol->SCR_.value[ListIndex]->reference = defaultSCR_.reference;
                    Patrol->SCR_.value[ListIndex]->isSCRO = defaultSCR_.isSCRO;
                    return;
                default:
                    return;
                }
            return;
        case 23: //topic
            if(Patrol.IsLoaded())
                Patrol->TNAM.Unload();
            return;
        case 24: //levelMod
            XLCM.Unload();
            return;
        case 25: //merchantContainer
            XMRC.Unload();
            return;
        case 26: //count
            XCNT.Unload();
            return;
        case 27: //radius
            XRDS.Unload();
            return;
        case 28: //health
            XHLP.Unload();
            return;
        case 29: //decals
            if(ListFieldID == 0) //decalsSize
                {
                XDCR.Unload();
                return;
                }

            if(ListIndex >= XDCR.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //reference
                    XDCR.value[ListIndex]->reference = defaultXDCR.reference;
                    return;
                case 2: //unknown1
                    memcpy(&XDCR.value[ListIndex]->unknown1[0], &defaultXDCR.unknown1[0], sizeof(XDCR.value[ListIndex]->unknown1));
                    return;
                default:
                    return;
                }
            return;
        case 30: //linkedReference
            XLKR.Unload();
            return;
        case 31: //startRed
            if(XCLP.IsLoaded())
                XCLP->start.red = defaultCLR.red;
            return;
        case 32: //startGreen
            if(XCLP.IsLoaded())
                XCLP->start.green = defaultCLR.green;
            return;
        case 33: //startBlue
            if(XCLP.IsLoaded())
                XCLP->start.blue = defaultCLR.blue;
            return;
        case 34: //unused2
            if(XCLP.IsLoaded())
                XCLP->start.unused1 = defaultCLR.unused1;
            return;
        case 35: //endRed
            if(XCLP.IsLoaded())
                XCLP->end.red = defaultCLR.red;
            return;
        case 36: //endGreen
            if(XCLP.IsLoaded())
                XCLP->end.green = defaultCLR.green;
            return;
        case 37: //endBlue
            if(XCLP.IsLoaded())
                XCLP->end.blue = defaultCLR.blue;
            return;
        case 38: //unused3
            if(XCLP.IsLoaded())
                XCLP->end.unused1 = defaultCLR.unused1;
            return;
        case 39: //activateParentFlags
            if(ActivateParents.IsLoaded())
                ActivateParents->XAPD.Unload();
            return;
        case 40: //activateParentRefs
            if(!ActivateParents.IsLoaded())
                return;

            if(ListFieldID == 0) //decalsSize
                {
                ActivateParents->XAPR.Unload();
                return;
                }

            if(ListIndex >= ActivateParents->XAPR.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //reference
                    ActivateParents->XAPR.value[ListIndex]->reference = defaultXAPR.reference;
                    return;
                case 2: //delay
                    ActivateParents->XAPR.value[ListIndex]->delay = defaultXAPR.delay;
                    return;
                default:
                    return;
                }
            return;
        case 41: //prompt
            XATO.Unload();
            return;
        case 42: //parent
            if(XESP.IsLoaded())
                XESP->parent = defaultXESP.parent;
            return;
        case 43: //parentFlags
            if(XESP.IsLoaded())
                SetFlagMask(defaultXESP.flags);
            return;
        case 44: //unused4
            if(XESP.IsLoaded())
                {
                XESP->unused1[0] = defaultXESP.unused1[0];
                XESP->unused1[1] = defaultXESP.unused1[1];
                XESP->unused1[2] = defaultXESP.unused1[2];
                }
            return;
        case 45: //emittance
            XEMI.Unload();
            return;
        case 46: //boundRef
            XMBR.Unload();
            return;
        case 47: //ignoredBySandbox
            XIBS.Unload();
            return;
        case 48: //scale
            XSCL.Unload();
            return;
        case 49: //posX
            DATA.value.posX = defaultDATA.posX;
            return;
        case 50: //posY
            DATA.value.posY = defaultDATA.posY;
            return;
        case 51: //posZ
            DATA.value.posZ = defaultDATA.posZ;
            return;
        case 52: //rotX
            DATA.value.rotX = defaultDATA.rotX;
            return;
        case 53: //rotY
            DATA.value.rotY = defaultDATA.rotY;
            return;
        case 54: //rotZ
            DATA.value.rotZ = defaultDATA.rotZ;
            return;
        default:
            return;
        }
    }
}