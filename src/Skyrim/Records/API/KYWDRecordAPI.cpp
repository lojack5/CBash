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
#include "../KYWDRecord.h"

namespace Sk
{

uint32_t KYWDRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
    case 7: //color.red
        return UINT8_FIELD;
    case 8: //color.green
        return UINT8_FIELD;
    case 9: //color.blue
        return UINT8_FIELD;
    case 10: //color.unk1
        return UINT8_FIELD;
    default:
        return UNKNOWN_FIELD;
    }
    return UNKNOWN_FIELD;
}

void * KYWDRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
    case 7: //color.red
        return &CNAM->red;
    case 8: //color.green
        return &CNAM->green;
    case 9: //color.blue
        return &CNAM->blue;
    case 10: //color.unk1
        return &CNAM->unk1;
    default:
        return NULL;
    }
    return NULL;
}

bool KYWDRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
    case 7: //color.red
        CNAM->red = *(uint8_t *)FieldValue;
        break;
    case 8: //color.green
        CNAM->green = *(uint8_t *)FieldValue;
        break;
    case 9: //color.green
        CNAM->blue = *(uint8_t *)FieldValue;
        break;
    case 10: //color.unk1
        CNAM->unk1 = *(uint8_t *)FieldValue;
        break;
    default:
        break;
    }
    return false;
}

void KYWDRecord::DeleteField(FIELD_IDENTIFIERS)
{
    GENCNAM defaultCNAM;
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
    case 7: //color.red
        CNAM->red = defaultCNAM.red;
        return;
    case 8: //color.green
        CNAM->green = defaultCNAM.green;
        return;
    case 9: //color.blue
        CNAM->blue = defaultCNAM.blue;
        return;
    case 10: //color.unk1
        CNAM->unk1 = defaultCNAM.unk1;
        return;
        return;
    default:
        return;
    }
}

} // namespace Sk
