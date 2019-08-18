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
#include "../SCPTRecord.h"

namespace Ob
{
uint32_t SCPTRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
    {
    switch(FieldID)
        {
        case 0: //recType
            return GetType();
        case 1: //flags1
            return UINT32_FLAG_FIELD;
        case 2: //fid
            return FORMID_FIELD;
        case 3: //flags2
            return UINT32_FLAG_FIELD;
        case 4: //eid
            return ISTRING_FIELD;
        case 5: //unused1
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
        case 6: //numRefs
            return UINT32_FIELD;
        case 7: //compiledSize
            return UINT32_FIELD;
        case 8: //lastIndex
            return UINT32_FIELD;
        case 9: //scriptType
            return UINT32_TYPE_FIELD;
        case 10: //compiled_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return SCDA.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 11: //scriptText
            return ISTRING_FIELD;
        case 12: //vars
            if(ListFieldID == 0) //vars
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)VARS.value.size();
                    default:
                        return UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= VARS.value.size())
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
                case 5: //name
                    return ISTRING_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 13: //references
            if(ListFieldID == 0) //references
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return FORMID_OR_UINT32_ARRAY_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)SCR_.value.size();
                    default:
                        return UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= SCR_.value.size())
                return UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //reference
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return FORMID_OR_UINT32_FIELD;
                        case 2: //WhichType
                            return (SCR_.value[ListIndex]->isSCRO ? FORMID_FIELD : UINT32_FIELD);
                        default:
                            return UNKNOWN_FIELD;
                        }
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * SCPTRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
    {
    switch(FieldID)
        {
        case 1: //flags1
            return &flags;
        case 2: //fid
            return &formID;
        case 3: //flags2
            return &flagsUnk;
        case 4: //eid
            return EDID.value;
        case 5: //unused1
            *FieldValues = &SCHR.value.unused1[0];
            return NULL;
        case 6: //numRefs
            return &SCHR.value.numRefs;
        case 7: //compiledSize
            return &SCHR.value.compiledSize;
        case 8: //lastIndex
            return &SCHR.value.lastIndex;
        case 9: //scriptType
            return &SCHR.value.scriptType;
        case 10: //compiled_p
            *FieldValues = SCDA.value;
            return NULL;
        case 11: //scriptText
            return SCTX.value;
        case 12: //vars
            if(ListIndex >= VARS.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //index
                    return &VARS.value[ListIndex]->SLSD.value.index;
                case 2: //unused1
                    *FieldValues = &VARS.value[ListIndex]->SLSD.value.unused1[0];
                    return NULL;
                case 3: //flags
                    return &VARS.value[ListIndex]->SLSD.value.flags;
                case 4: //unused2
                    *FieldValues = &VARS.value[ListIndex]->SLSD.value.unused2[0];
                    return NULL;
                case 5: //name
                    return VARS.value[ListIndex]->SCVR.value;
                default:
                    return NULL;
                }
            return NULL;
        case 13: //references
            for(uint32_t x = 0; x < SCR_.value.size(); ++x)
                ((FORMIDARRAY)FieldValues)[x] = SCR_.value[x]->reference;
            return NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool SCPTRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(*(uint32_t *)FieldValue);
            break;
        case 3: //flags2
            SetHeaderUnknownFlagMask(*(uint32_t *)FieldValue);
            break;
        case 4: //eid
            EDID.Copy((char *)FieldValue);
            break;
        case 5: //unused1
            if(ArraySize != 4)
                break;
            SCHR.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            SCHR.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            SCHR.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            SCHR.value.unused1[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 6: //numRefs
            SCHR.value.numRefs = *(uint32_t *)FieldValue;
            break;
        case 7: //compiledSize
            SCHR.value.compiledSize = *(uint32_t *)FieldValue;
            break;
        case 8: //lastIndex
            SCHR.value.lastIndex = *(uint32_t *)FieldValue;
            break;
        case 9: //scriptType
            SetType(*(uint32_t *)FieldValue);
            break;
        case 10: //compiled_p
            SCDA.Copy((UINT8ARRAY)FieldValue, ArraySize);
            SCHR.value.compiledSize = ArraySize;
            break;
        case 11: //scriptText
            SCTX.Copy((char *)FieldValue);
            break;
        case 12: //vars
            if(ListFieldID == 0) //varsSize
                {
                VARS.resize(ArraySize);
                }

            if(ListIndex >= VARS.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //index
                    VARS.value[ListIndex]->SLSD.value.index = *(uint32_t *)FieldValue;
                    break;
                case 2: //unused1
                    if(ArraySize != 12)
                        break;
                    VARS.value[ListIndex]->SLSD.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                    VARS.value[ListIndex]->SLSD.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                    VARS.value[ListIndex]->SLSD.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
                    VARS.value[ListIndex]->SLSD.value.unused1[3] = ((UINT8ARRAY)FieldValue)[3];
                    VARS.value[ListIndex]->SLSD.value.unused1[4] = ((UINT8ARRAY)FieldValue)[4];
                    VARS.value[ListIndex]->SLSD.value.unused1[5] = ((UINT8ARRAY)FieldValue)[5];
                    VARS.value[ListIndex]->SLSD.value.unused1[6] = ((UINT8ARRAY)FieldValue)[6];
                    VARS.value[ListIndex]->SLSD.value.unused1[7] = ((UINT8ARRAY)FieldValue)[7];
                    VARS.value[ListIndex]->SLSD.value.unused1[8] = ((UINT8ARRAY)FieldValue)[8];
                    VARS.value[ListIndex]->SLSD.value.unused1[9] = ((UINT8ARRAY)FieldValue)[9];
                    VARS.value[ListIndex]->SLSD.value.unused1[10] = ((UINT8ARRAY)FieldValue)[10];
                    VARS.value[ListIndex]->SLSD.value.unused1[11] = ((UINT8ARRAY)FieldValue)[11];
                    break;
                case 3: //flags
                    VARS.value[ListIndex]->SetFlagMask(*(uint8_t *)FieldValue);
                    break;
                case 4: //unused2
                    if(ArraySize != 7)
                        break;
                    VARS.value[ListIndex]->SLSD.value.unused2[0] = ((UINT8ARRAY)FieldValue)[0];
                    VARS.value[ListIndex]->SLSD.value.unused2[1] = ((UINT8ARRAY)FieldValue)[1];
                    VARS.value[ListIndex]->SLSD.value.unused2[2] = ((UINT8ARRAY)FieldValue)[2];
                    VARS.value[ListIndex]->SLSD.value.unused2[3] = ((UINT8ARRAY)FieldValue)[3];
                    VARS.value[ListIndex]->SLSD.value.unused2[4] = ((UINT8ARRAY)FieldValue)[4];
                    VARS.value[ListIndex]->SLSD.value.unused2[5] = ((UINT8ARRAY)FieldValue)[5];
                    VARS.value[ListIndex]->SLSD.value.unused2[6] = ((UINT8ARRAY)FieldValue)[6];
                    break;
                case 5: //name
                    VARS.value[ListIndex]->SCVR.Copy((char *)FieldValue);
                    break;
                default:
                    break;
                }
            break;
        case 13: //references
            if(ListFieldID == 0) //referencesSize
                {
                SCR_.resize(ArraySize);
                return false;
                }

            if(ListIndex >= SCR_.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //reference
                    //Borrowing ArraySize to flag if the new value is a formID
                    SCR_.value[ListIndex]->reference = *(uint32_t *)FieldValue;
                    SCR_.value[ListIndex]->isSCRO = ArraySize ? true : false;
                    return ArraySize != 0;
                default:
                    break;
                }
            break;
        default:
            break;
        }
    return false;
    }

void SCPTRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    GENSCHR defaultSCHR;

    GENVARS defaultVARS;
    GENSCR_ defaultSCR_;

    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(0);
            return;
        case 3: //flags2
            flagsUnk = 0;
            return;
        case 4: //eid
            EDID.Unload();
            return;
        case 5: //unused1
            SCHR.value.unused1[0] = defaultSCHR.unused1[0];
            SCHR.value.unused1[1] = defaultSCHR.unused1[1];
            SCHR.value.unused1[2] = defaultSCHR.unused1[2];
            SCHR.value.unused1[3] = defaultSCHR.unused1[3];
            return;
        case 6: //numRefs
            SCHR.value.numRefs = defaultSCHR.numRefs;
            return;
        case 7: //compiledSize
            SCHR.value.compiledSize = defaultSCHR.compiledSize;
            return;
        case 8: //lastIndex
            SCHR.value.lastIndex = defaultSCHR.lastIndex;
            return;
        case 9: //scriptType
            SCHR.value.scriptType = defaultSCHR.scriptType;
            return;
        case 10: //compiled_p
            SCDA.Unload();
            return;
        case 11: //scriptText
            SCTX.Unload();
            return;
        case 12: //vars
            if(ListFieldID == 0) //vars
                {
                VARS.Unload();
                return;
                }

            if(ListIndex >= VARS.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //index
                    VARS.value[ListIndex]->SLSD.value.index = defaultVARS.SLSD.value.index;
                    return;
                case 2: //unused1
                    VARS.value[ListIndex]->SLSD.value.unused1[0] = defaultVARS.SLSD.value.unused1[0];
                    VARS.value[ListIndex]->SLSD.value.unused1[1] = defaultVARS.SLSD.value.unused1[1];
                    VARS.value[ListIndex]->SLSD.value.unused1[2] = defaultVARS.SLSD.value.unused1[2];
                    VARS.value[ListIndex]->SLSD.value.unused1[3] = defaultVARS.SLSD.value.unused1[3];
                    VARS.value[ListIndex]->SLSD.value.unused1[4] = defaultVARS.SLSD.value.unused1[4];
                    VARS.value[ListIndex]->SLSD.value.unused1[5] = defaultVARS.SLSD.value.unused1[5];
                    VARS.value[ListIndex]->SLSD.value.unused1[6] = defaultVARS.SLSD.value.unused1[6];
                    VARS.value[ListIndex]->SLSD.value.unused1[7] = defaultVARS.SLSD.value.unused1[7];
                    VARS.value[ListIndex]->SLSD.value.unused1[8] = defaultVARS.SLSD.value.unused1[8];
                    VARS.value[ListIndex]->SLSD.value.unused1[9] = defaultVARS.SLSD.value.unused1[9];
                    VARS.value[ListIndex]->SLSD.value.unused1[10] = defaultVARS.SLSD.value.unused1[10];
                    VARS.value[ListIndex]->SLSD.value.unused1[11] = defaultVARS.SLSD.value.unused1[11];
                    return;
                case 3: //flags
                    VARS.value[ListIndex]->SLSD.value.flags = defaultVARS.SLSD.value.flags;
                    return;
                case 4: //unused2
                    VARS.value[ListIndex]->SLSD.value.unused2[0] = defaultVARS.SLSD.value.unused2[0];
                    VARS.value[ListIndex]->SLSD.value.unused2[1] = defaultVARS.SLSD.value.unused2[1];
                    VARS.value[ListIndex]->SLSD.value.unused2[2] = defaultVARS.SLSD.value.unused2[2];
                    VARS.value[ListIndex]->SLSD.value.unused2[3] = defaultVARS.SLSD.value.unused2[3];
                    VARS.value[ListIndex]->SLSD.value.unused2[4] = defaultVARS.SLSD.value.unused2[4];
                    VARS.value[ListIndex]->SLSD.value.unused2[5] = defaultVARS.SLSD.value.unused2[5];
                    VARS.value[ListIndex]->SLSD.value.unused2[6] = defaultVARS.SLSD.value.unused2[6];
                    return;
                case 5: //name
                    VARS.value[ListIndex]->SCVR.Unload();
                    return;
                default:
                    return;
                }
            return;
        case 13: //references
            if(ListFieldID == 0) //references
                {
                SCR_.Unload();
                return;
                }

            if(ListIndex >= SCR_.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //reference
                    SCR_.value[ListIndex]->reference = defaultSCR_.reference;
                    SCR_.value[ListIndex]->isSCRO = defaultSCR_.isSCRO;
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