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
* Dienes.
* Portions created by the Initial Developer are Copyright (C) 2014
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
#include "../NPC_Record.h"

namespace Sk
{

// VMAD not accessible via API

uint32_t NPC_Record::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
{
    switch (FieldID)
    {
    case 0: //recType
        return GetType();
    case 1: //flags1
        return UINT32_FLAG_FIELD;
    case 2: //fid
        return FORMID_FIELD;
    case 3: //versionControl1
        switch (WhichAttribute)
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
        switch (WhichAttribute)
        {
        case 0: //fieldType
            return UINT8_ARRAY_FIELD;
        case 1: //fieldSize
            return 2;
        default:
            return UNKNOWN_FIELD;
        }
        return UNKNOWN_FIELD;
    // start OBND
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
    // start ACBS
    case 13: // flags
        return UINT32_FLAG_FIELD;
    case 14: // magickaOffset
        return UINT16_FIELD;
    case 15: // staminaOffset
        return UINT16_FIELD;
    case 16: // Level or level mult
        return SINT16_FIELD;
    case 17: // calcMinLevel
        return UINT16_FIELD;
    case 18: // calcMaxLevel
        return UINT16_FIELD;
    case 19: // speedMultiplier
        return UINT16_FIELD;
    case 20: // dispositionBase_unused
        return SINT16_FIELD;
    case 21: // templateFlags
        return UINT16_FLAG_FIELD;
    case 22: // healthOffset
        return UINT16_FIELD;
    case 23: // bleedoutOverride
        return UINT16_FIELD;
    // start SNAM
    case 24: // faction
        if (ListFieldID == 0) //factions
        {
            switch (WhichAttribute)
            {
            case 0: //fieldType
                return LIST_FIELD;
            case 1: //fieldSize
                return SNAM.IsLoaded() ? (uint32_t)SNAM.value.size() : 0;
            default:
                return UNKNOWN_FIELD;
            }
        }

        if (ListIndex >= SNAM.value.size())
            return UNKNOWN_FIELD;

        switch (ListFieldID)
        {
        case 1: //faction
            return FORMID_FIELD;
        case 2: //rank
            return UINT8_FIELD;
        case 3: //unused1
            switch (WhichAttribute)
            {
            case 0: //fieldType
                return UINT8_ARRAY_FIELD;
            case 1: //fieldSize
                return 3;
            default:
                return UNKNOWN_FIELD;
            }
        default:
            return UNKNOWN_FIELD;
        }
        return UNKNOWN_FIELD;
    case 25: // INAM - death item
        return FORMID_FIELD;
    case 26: // VTCK - voice
        return FORMID_FIELD;
    case 27: // TPLT template
        return FORMID_FIELD;
    case 28: // RNAM
        return FORMID_FIELD;
    // start SPLO
    case 29: // SPLO
        switch (WhichAttribute)
        {
        case 0: //fieldType
            return FORMID_ARRAY_FIELD;
        case 1: //fieldSize
            return SPLO.value.size();
        default:
            return UNKNOWN_FIELD;
        }
        return UNKNOWN_FIELD;
    // start destructables
    //DEST header
    case 30: //destructableHealth
        return SINT32_FIELD;
    case 31: //destructableCount
        return UINT8_FIELD;
    case 32: //destructableFlags
        return UINT8_FLAG_FIELD;
    case 33: //destructableUnused1
        switch (WhichAttribute)
        {
        case 0: //fieldType
            return UINT8_ARRAY_FIELD;
        case 1: //fieldSize
            return Destructable.IsLoaded() ? 2 : 0;
        default:
            return UNKNOWN_FIELD;
        }
        return UNKNOWN_FIELD;
    case 34: //destructableStages
        if (!Destructable.IsLoaded())
            return UNKNOWN_FIELD;

        if (ListFieldID == 0) //destructableStages
        {
            switch (WhichAttribute)
            {
            case 0: //fieldType
                return LIST_FIELD;
            case 1: //fieldSize
                return (uint32_t)Destructable->Stages.value.size();
            default:
                return UNKNOWN_FIELD;
            }
        }

        if (ListIndex >= Destructable->Stages.value.size())
            return UNKNOWN_FIELD;

        switch (ListFieldID)
        {
        case 1: //health
            return UINT8_FIELD;
        case 2: //index
            return UINT8_FIELD;
        case 3: //stage
            return UINT8_FIELD;
        case 4: //flags
            return UINT8_FLAG_FIELD;
        case 5: //dps
            return SINT32_FIELD;
        case 6: //explosion
            return FORMID_FIELD;
        case 7: //debris
            return FORMID_FIELD;
        case 8: //debrisCount
            return SINT32_FIELD;
        case 9: //modPath
            return ISTRING_FIELD;
        case 10: //modt_p
            switch (WhichAttribute)
            {
            case 0: //fieldType
                return UINT8_ARRAY_FIELD;
            case 1: //fieldSize
                return Destructable->Stages.value[ListIndex]->DMDT.GetSize();
            default:
                return UNKNOWN_FIELD;
            }
            return UNKNOWN_FIELD;
        case 11: //altTextures
            if (ListX2FieldID == 0) //altTextures
            {
                switch (WhichAttribute)
                {
                case 1: //fieldType
                    return LIST_FIELD;
                case 2: //fieldSize
                    return Destructable->Stages.value[ListIndex]->DMDS.MODS.size();
                default:
                    return UNKNOWN_FIELD;
                }
                return UNKNOWN_FIELD;
            }
            if (ListX2Index >= Destructable->Stages.value[ListIndex]->DMDS.MODS.size())
                return UNKNOWN_FIELD;
            switch (ListX2FieldID)
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
        default:
            return UNKNOWN_FIELD;
        }
        return UNKNOWN_FIELD;
    // end DEST
    case 35: // WNAM
        return FORMID_FIELD;
    case 36: // ANAM
        return FORMID_FIELD;
    case 37: // ATKR
        return FORMID_FIELD;
    // start attacks
    case 38: 
        if (ListFieldID == 0) // attacks
        {
            switch (WhichAttribute)
            {
            case 0: //fieldType
                return LIST_FIELD;
            case 1: //fieldSize
                return (uint32_t)attacks.value.size();
            default:
                return UNKNOWN_FIELD;
            }
        }

        if (ListIndex >= attacks.value.size())
            return UNKNOWN_FIELD;

        switch (ListFieldID)
        {
        case 1: // damageMult
            return FLOAT32_FIELD;
        case 2: // attackChance
            return FLOAT32_FIELD;
        case 3: // attackSpell
            return FORMID_FIELD;
        case 4: // flags
            return UINT32_FLAG_TYPE_FIELD;
        case 5: // attackAngle
            return FLOAT32_FIELD;
        case 6: // strikeAngle
            return FLOAT32_FIELD;
        case 7: // stagger
            return FLOAT32_FIELD;
        case 8: // attackType
            return FORMID_FIELD;
        case 9: // knockdown
            return FLOAT32_FIELD;
        case 10: // recoveryTime
            return FLOAT32_FIELD;
        case 11: // fatigueMult
            return FLOAT32_FIELD;
        case 12: // ATKE
            return ISTRING_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    //end attacks
    case 39: // SPOR
        return FORMID_FIELD;
    case 40: // OCOR
        return FORMID_FIELD;
    case 41: // GWOR
        return FORMID_FIELD;
    case 42: // ECOR
        return FORMID_FIELD;
    // start Perks
    case 43: // PRKR
        if (ListFieldID == 0) // perks
        {
            switch (WhichAttribute)
            {
            case 0: //fieldType
                return LIST_FIELD;
            case 1: //fieldSize
                return (uint32_t)PRKR.value.size();
            default:
                return UNKNOWN_FIELD;
            }
        }

        if (ListIndex >= PRKR.value.size())
            return UNKNOWN_FIELD;

        switch (ListFieldID)
        {
        case 1: // perk
            return FORMID_FIELD;
        case 2: // rank
            return UINT8_TYPE_FIELD;
        case 3: // unused
        case 4:
        case 5:
            return UNKNOWN_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    // end perks
    // start items
    case 44:
        if (ListFieldID == 0) // items
        {
            switch (WhichAttribute)
            {
            case 0: //fieldType
                return LIST_FIELD;
            case 1: //fieldSize
                return (uint32_t)CNTO.value.size();
            default:
                return UNKNOWN_FIELD;
            }
        }

        if (ListIndex >= CNTO.value.size())
            return UNKNOWN_FIELD;

        switch (ListFieldID)
        {
        case 1: // CNTO item
            return FORMID_FIELD;
        case 2: // CNTO count
            return UINT32_TYPE_FIELD;
        case 3: // COED owner
            return FORMID_FIELD;
        case 4: // COED globalOrRank
            switch (WhichAttribute)
            {
            case 0: //fieldType
                return UNKNOWN_OR_FORMID_OR_UINT32_FIELD;
            case 2: //WhichType
                return FORMID_FIELD;
            default:
                return UNKNOWN_FIELD;
            }
            return UNKNOWN_FIELD;
        case 5: //condition
            return FLOAT32_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    // end items
    // start AIDT
    case 45: // aggression
    case 46: // confidence
    case 47: // energyLevel
    case 48: // responsibility
    case 49: // mood
    case 50: // assistance
        return UINT8_TYPE_FIELD;
    case 51: // agro agroRadiusBehavior
    case 52: // agro unused
        return UINT8_TYPE_FIELD;
    case 53: // warn
    case 54: // warnAttack
    case 55: // attack
        return UINT32_TYPE_FIELD;
    // end AIDT
    case 56: // packages
        switch (WhichAttribute)
        {
        case 0: //fieldType
            return FORMID_ARRAY_FIELD;
        case 1: //fieldSize
            return PKID.value.size();
        default:
            return UNKNOWN_FIELD;
        }
        return UNKNOWN_FIELD;
    case 57: // keywords
        switch (WhichAttribute)
        {
        case 0: //fieldType
            return FORMID_ARRAY_FIELD;
        case 1: //fieldSize
            return KWDA.value.size();
        default:
            return UNKNOWN_FIELD;
        }
        return UNKNOWN_FIELD;
    case 58: // CNAM
        return FORMID_FIELD;
    case 59: // FULL
        return STRING_FIELD;
    case 60: // SHRT
        return STRING_FIELD;
    case 61: // DNAM


    default:
        return UNKNOWN_FIELD;
    }
    return UNKNOWN_FIELD;
}

void * NPC_Record::GetField(FIELD_IDENTIFIERS, void **FieldValues)
{
	return NULL;
}

bool NPC_Record::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
{
	return true;
}

void NPC_Record::DeleteField(FIELD_IDENTIFIERS)
{

}

} // namespace Sk