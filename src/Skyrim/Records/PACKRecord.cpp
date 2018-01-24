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
#include "../../Common.h"
#include "PACKRecord.h"
#include "../../Oblivion/Records/PACKRecord.h"

namespace Sk
{

PACKRecord::PACKPKDT::PACKPKDT():
    flags(0),
    packageType(0x12),
    interruptOverride(0),
    preferredSpeed(0),
    unused1(0),
    interruptFlags(0)
    {
    }

PACKRecord::PACKPKDT::~PACKPKDT()
    {
    //
    }

PACKRecord::PACKPKCU::PACKPKCU():
dataInputCount(0),
packageTemplate(0),
versionCounter(0)
{
    //
}

PACKRecord::PACKPKCU::~PACKPKCU()
{
    //
}


bool PACKRecord::PACKPKDT::operator ==(const PACKPKDT &other) const
    {
    return (flags == other.flags &&
            packageType == other.packageType &&
            interruptOverride == other.interruptOverride &&
            interruptOverride == other.interruptOverride &&
            preferredSpeed == other.preferredSpeed &&
            interruptFlags == other.interruptFlags);
    }

bool PACKRecord::PACKPKDT::operator !=(const PACKPKDT &other) const
    {
    return !(*this == other);
    }

PACKRecord::PACKPLDT::PACKPLDT():
    locType(0),
    locId(0),
    locRadius(0)
    {
    //
    }

PACKRecord::PACKPLDT::~PACKPLDT()
    {
    //
    }

bool PACKRecord::PACKPLDT::operator ==(const PACKPLDT &other) const
    {
    return (locType == other.locType &&
            locId == other.locId &&
            locRadius == other.locRadius);
    }

bool PACKRecord::PACKPLDT::operator !=(const PACKPLDT &other) const
    {
    return !(*this == other);
    }

PACKRecord::PACKPSDT::PACKPSDT():
    month(0),
    day(0),
    date(0),
    hour(0),
    minute(0),
    duration(0)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    }

PACKRecord::PACKPSDT::~PACKPSDT()
    {
    //
    }

bool PACKRecord::PACKPSDT::operator ==(const PACKPSDT &other) const
    {
    return (month == other.month &&
            day == other.day &&
            date == other.date &&
            hour == other.hour &&
            minute == other.minute &&
            duration == other.duration);
    }

bool PACKRecord::PACKPSDT::operator !=(const PACKPSDT &other) const
    {
    return !(*this == other);
    }

PACKRecord::PACKPTDA::PACKPTDA():
    targetType(0),
    targetId(0),
    targetCount(0)
    {
    //
    }

PACKRecord::PACKPTDA::~PACKPTDA()
    {
    //
    }

bool PACKRecord::PACKPTDA::operator ==(const PACKPTDA &other) const
    {
    return (targetType == other.targetType &&
            targetId == other.targetId &&
            targetCount == other.targetCount);
    }

bool PACKRecord::PACKPTDA::operator !=(const PACKPTDA &other) const
    {
    return !(*this == other);
    }

PACKRecord::PACKRecord(unsigned char *_recData):
    TES5Record(_recData)
    {
    //
    }

PACKRecord::PACKRecord(PACKRecord *srcRecord):
TES5Record()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;
    formVersion = srcRecord->formVersion;
    versionControl2[0] = srcRecord->versionControl2[0];


    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;
    CTDA = srcRecord->CTDA;
    PKCU = srcRecord->PKCU;
    PKDT = srcRecord->PKDT;
    PSDT = srcRecord->PSDT;
    TDAT = srcRecord->TDAT;
    return;
    }

PACKRecord::~PACKRecord()
    {
    //
    }

bool PACKRecord::VisitFormIDs(FormIDOp &op)
    {

    if(!IsLoaded())
        return false;

    op.Accept(PKCU.value.packageTemplate);

    for(uint32_t ListIndex = 0; ListIndex < CTDA.value.size(); ListIndex++) {
        CTDA.value[ListIndex]->VisitFormIDs(op);
    }
    for(uint32_t ListIndex = 0; ListIndex < TDAT.ANAM.size(); ListIndex++) {
        
        if (TDAT.ANAM[ListIndex] == "Location") {

            if ((TDAT.cnamData[ListIndex].writtenPLDT.locId == 0x07) || (TDAT.cnamData[ListIndex].writtenPLDT.locId == 0x01000007) || (TDAT.cnamData[ListIndex].writtenPLDT.locId == 0x01000014)) {
                TDAT.cnamData[ListIndex].writtenPLDT.locId = 0x14;
            }

            op.Accept((TDAT.cnamData[ListIndex].writtenPLDT.locId));        
        }
        
        if (TDAT.ANAM[ListIndex] == "SingleRef" || TDAT.ANAM[ListIndex] == "TargetSelector") {

            if ((TDAT.cnamData[ListIndex].writtenPTDA.targetId == 0x07) || (TDAT.cnamData[ListIndex].writtenPTDA.targetId == 0x01000007) || (TDAT.cnamData[ListIndex].writtenPTDA.targetId == 0x01000014)) {
                TDAT.cnamData[ListIndex].writtenPTDA.targetId = 0x14;
            }

            op.Accept((TDAT.cnamData[ListIndex].writtenPTDA.targetId));        
        }
        
    }

    return op.Stop();
    }

bool PACKRecord::isMustComplete() { return (PKDT.value.flags & fMustComplete) != 0; }
bool PACKRecord::isMaintainSpeedAtGoal() { return (PKDT.value.flags & fMaintainSpeedAtGoal) != 0; }
bool PACKRecord::isAtPackageStartUnlockDoors() { return (PKDT.value.flags & fAtPackageStartUnlockDoors) != 0; }
bool PACKRecord::isAtPackageChangeUnlockDoors() { return (PKDT.value.flags & fAtPackageChangeUnlockDoors) != 0; }
bool PACKRecord::isOncePerDay() { return (PKDT.value.flags & fOncePerDay) != 0; }
bool PACKRecord::isPreferredSpeed() { return (PKDT.value.flags & fPreferredSpeed) != 0; }
bool PACKRecord::isAlwaysSneak() { return (PKDT.value.flags & fAlwaysSneak) != 0; }
bool PACKRecord::isAllowSwimming() { return (PKDT.value.flags & fAllowSwimming) != 0; }
bool PACKRecord::isIgnoreCombat() { return (PKDT.value.flags & fIgnoreCombat) != 0; }
bool PACKRecord::isWeaponsUnequipped() { return (PKDT.value.flags & fWeaponsUnequipped) != 0; }
bool PACKRecord::isWeaponDrawn() { return (PKDT.value.flags & fWeaponDrawn) != 0; }
bool PACKRecord::isNoCombatAlert() { return (PKDT.value.flags & fNoCombatAlert) != 0; }
bool PACKRecord::isWearSleepOutfit() { return (PKDT.value.flags & fWearSleepOutfit) != 0; }
/*
bool PACKRecord::isHellosToPlayer() { return (PKDT.value.interruptFlags & PACKRecord::interrupt) != 0; }
bool PACKRecord::isRandomConversations() { return (PKDT.value.interruptFlags & fRandomConversations) != 0; }
bool PACKRecord::isObserveCombatBehavior() { return (PKDT.value.interruptFlags & fObserveCombatBehavior) != 0; }
bool PACKRecord::isGreetCorpseBehavior() { return (PKDT.value.interruptFlags & fGreetCorpseBehavior) != 0; }
bool PACKRecord::isReactionToPlayerActions() { return (PKDT.value.interruptFlags & fReactionToPlayerActions) != 0; }
bool PACKRecord::isFriendlyFireComments() { return (PKDT.value.interruptFlags & fFriendlyFireComments) != 0; }
bool PACKRecord::isAggroRadiusBehavior() { return (PKDT.value.interruptFlags & fAggroRadiusBehavior) != 0; }
bool PACKRecord::isAllowIdleChatter() { return (PKDT.value.interruptFlags & fAllowIdleChatter) != 0; }
bool PACKRecord::isWorldInteractions() { return (PKDT.value.interruptFlags & fWorldInteractions) != 0; }
*/

uint32_t PACKRecord::GetType()
    {
    return REV32(PACK);
    }

char* PACKRecord::GetStrType()
    {
    return "PACK";
    }

int32_t PACKRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
    uint32_t subType = 0;
    uint32_t subSize = 0;
    bool hasReachedOptionalSection = false;
    bool hasReachedTemplateSkippedData = false;
    SKCondition *current_condition = NULL;

    while(buffer < end_buffer){
        subType = *(uint32_t *)buffer;
        buffer += 4;


        switch(subType)
            {
            case REV32(XXXX):
                buffer += 2;
                subSize = *(uint32_t *)buffer;
                buffer += 4;
                subType = *(uint32_t *)buffer;
                buffer += 6;
                break;
            default:
                subSize = *(uint16_t *)buffer;
                buffer += 2;
                break;
            }

        if (hasReachedTemplateSkippedData) {
            buffer += subSize;
            continue; //We just skip the records if this flag is on
        }

        switch(subType)
            {
            case REV32(EDID):
                EDID.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(PKDT):
                PKDT.Read(buffer, subSize);
                break;
            case REV32(PSDT):
                PSDT.Read(buffer, subSize);
                break;
            case REV32(PKCU):
                PKCU.Read(buffer, subSize);
                break;
            case REV32(CTDT):
            case REV32(CTDA):
                current_condition = new SKCondition();
                CTDA.value.push_back(current_condition);
                current_condition->CTDA.Read(buffer, subSize);
                break;


            case REV32(CIS1):
                if (current_condition == NULL) {
                    printer("  INFO: %08X - Reading CIS1 without current_condition set\n", formID);
                    CBASH_CHUNK_DEBUG
                        printer("  Size = %i\n", subSize);
                    printer("  CurPos = %08x\n\n", buffer - 6);
                    buffer = end_buffer;
                }
                else {
                    current_condition->CIS1.Read(buffer, subSize, CompressedOnDisk);
                }

                break;

            case REV32(CIS2):
                if (current_condition == NULL) {
                    printer("  INFO: %08X - Reading CIS2 without current_condition set\n", formID);
                    CBASH_CHUNK_DEBUG
                        printer("  Size = %i\n", subSize);
                    printer("  CurPos = %08x\n\n", buffer - 6);
                    buffer = end_buffer;
                }
                else {
                    current_condition->CIS2.Read(buffer, subSize, CompressedOnDisk);
                }

                break;
            case REV32(ANAM):    
                hasReachedOptionalSection = true;
                TDAT.ReadANAM(buffer, subSize);
                break;
            case REV32(CNAM):
                if (hasReachedOptionalSection) {
                    TDAT.ReadSelector(buffer, subSize); //CNAM is a primitive value for the optional section
                }
                else {
                    CNAM.Read(buffer, subSize); //CNAM is a pointer to combat style
                }
                break;
            case REV32(PLDT):
            case REV32(PTDA):
                TDAT.ReadSelector(buffer, subSize);
                break;
            case REV32(UNAM):
                TDAT.ReadUNAM(buffer, subSize);
                break;
            case REV32(XNAM):
                //XNAM.Read(buffer, subSize);
                hasReachedTemplateSkippedData = true;
                buffer += subSize;
                break;
            default:
                log_debug << "PLDT debug " << REV32(PLDT) << std::endl;
                CBASH_SUBTYPE_UNKNOWN
                CBASH_CHUNK_DEBUG
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t PACKRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
   
    EDID.Unload();
    PKDT.Unload();
    PSDT.Unload();    
    CTDA.Unload();
    return 1;
    }

int32_t PACKRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(PKDT);
    WRITE(PSDT);
    CTDA.Write(writer, true);
    WRITE(PKCU);
    TDAT.Write(writer);
    //WRITE(XNAM);

    return -1;
    }

bool PACKRecord::operator ==(const PACKRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            PKDT == other.PKDT &&
            PSDT == other.PSDT &&
            CTDA == other.CTDA);
    }

bool PACKRecord::operator !=(const PACKRecord &other) const
    {
    return !(*this == other);
    }

bool PACKRecord::equals(Record *other)
    {
    return *this == *(PACKRecord *)other;
    }


}