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
#include "FACTRecord.h"

namespace Sk
{

void FACTRecord::FACTRNAM::Write(FileWriter &writer)
    {
    WRITE(RNAM);
    WRITE(MNAM);
    WRITE(FNAM);
    }

bool FACTRecord::FACTRNAM::operator ==(const FACTRNAM &other) const
    {
    return (RNAM == other.RNAM &&
            MNAM.equals(other.MNAM) &&
            FNAM.equals(other.FNAM));
    }

bool FACTRecord::FACTRNAM::operator !=(const FACTRNAM &other) const
    {
    return !(*this == other);
    }

FACTRecord::FACTRecord(unsigned char *_recData):
    TES5Record(_recData)
    {
    //
    }

FACTRecord::FACTRecord(FACTRecord *srcRecord):
    TES5Record()
    {
        if(srcRecord == NULL)
            return;

        flags = srcRecord->flags;
        formID = srcRecord->formID;
        flagsUnk = srcRecord->flagsUnk;
        formVersion = srcRecord->formVersion;
        versionControl2[0] = srcRecord->versionControl2[0];
        versionControl2[1] = srcRecord->versionControl2[1];

        recData = srcRecord->recData;
        if(!srcRecord->IsChanged())
            return;

        EDID = srcRecord->EDID;
        FULL = srcRecord->FULL;
        XNAM = srcRecord->XNAM;
        DATA = srcRecord->DATA;
        JAIL = srcRecord->JAIL;
        WAIT = srcRecord->WAIT;
        STOL = srcRecord->STOL;
        PLCN = srcRecord->PLCN;
        CRGR = srcRecord->CRGR;
        JOUT = srcRecord->JOUT;
        CRVA = srcRecord->CRVA;            
        RNAM = srcRecord->RNAM;
        VEND = srcRecord->VEND;
        VENC = srcRecord->VENC;
        VENV = srcRecord->VENV;
        PLVD = srcRecord->PLVD;
        CTDA = srcRecord->CTDA;
        return;
    }

FACTRecord::~FACTRecord()
    {
    //
    }

bool FACTRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(uint32_t ListIndex = 0; ListIndex < XNAM.value.size(); ListIndex++)
        op.Accept(XNAM.value[ListIndex]->faction);
    
    if(JAIL.IsLoaded()) op.Accept(JAIL.value);
    if(WAIT.IsLoaded()) op.Accept(WAIT.value);
    if(STOL.IsLoaded()) op.Accept(STOL.value);
    if(PLCN.IsLoaded()) op.Accept(PLCN.value);
    if(CRGR.IsLoaded()) op.Accept(CRGR.value);
    if(JOUT.IsLoaded()) op.Accept(JOUT.value);
    if(VEND.IsLoaded()) op.Accept(VEND.value);
    if(VENC.IsLoaded()) op.Accept(VENC.value);
    if(CTDA.IsLoaded()) {
        for(uint32_t Ind = 0; Ind < CTDA.value.size(); Ind++)
            CTDA.value[Ind]->VisitFormIDs(op);    
    }
    
    return op.Stop();
    }

bool FACTRecord::IsHiddenFromPC()
    {
    return (DATA.value & fIsHiddenFromPC) != 0;
    }

void FACTRecord::IsHiddenFromPC(bool value)
    {
    SETBIT(DATA.value, fIsHiddenFromPC, value);
    }

bool FACTRecord::IsEvil()
    {
    return (DATA.value & fIsEvil) != 0;
    }

void FACTRecord::IsEvil(bool value)
    {
    SETBIT(DATA.value, fIsEvil, value);
    }

bool FACTRecord::IsSpecialCombat()
    {
    return (DATA.value & fIsSpecialCombat) != 0;
    }

void FACTRecord::IsSpecialCombat(bool value)
    {
    SETBIT(DATA.value, fIsSpecialCombat, value);
    }

bool FACTRecord::IsTrackCrime()
    {
    return (DATA.value & fIsTrackCrime) != 0;
    }

void FACTRecord::IsTrackCrime(bool value)
    {
    SETBIT(DATA.value, fIsTrackCrime, value);
    }

bool FACTRecord::IsAllowSell()
    {
    return (DATA.value & fIsAllowSell) != 0;
    }

void FACTRecord::IsAllowSell(bool value)
    {
    SETBIT(DATA.value, fIsAllowSell, value);
    }

bool FACTRecord::IsFlagMask(uint16_t Mask, bool Exact)
    {
    return Exact ? ((DATA.value & Mask) == Mask) : ((DATA.value & Mask) != 0);
    }

void FACTRecord::SetFlagMask(uint16_t Mask)
    {
    DATA.value = Mask;
    }

uint32_t FACTRecord::GetType()
    {
    return REV32(FACT);
    }

char * FACTRecord::GetStrType()
    {
    return "FACT";
    }

int32_t FACTRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
    uint32_t subType = 0;
    uint32_t subSize = 0;
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
        switch(subType)
            {
            case REV32(EDID):
                EDID.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(XNAM):
                XNAM.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(JAIL):
                JAIL.Read(buffer, subSize);
                break;
            case REV32(WAIT):
                WAIT.Read(buffer, subSize);
                break;
            case REV32(STOL):
                STOL.Read(buffer, subSize);
                break;
            case REV32(PLCN):
                PLCN.Read(buffer, subSize);
                break;
            case REV32(CRGR):
                CRGR.Read(buffer, subSize);
                break;
            case REV32(JOUT):
                JOUT.Read(buffer, subSize);
                break;
            case REV32(CRVA):
                CRVA.Read(buffer, subSize);
                break;
            case REV32(RNAM):
                RNAM.value.push_back(new FACTRNAM);
                RNAM.value.back()->RNAM.Read(buffer, subSize);
                break;
            case REV32(VEND):
                VEND.Read(buffer, subSize);
                break;
            case REV32(VENC):
                VENC.Read(buffer, subSize);
                break;
            case REV32(VENV):
                VENV.Read(buffer, subSize);
                break;
            case REV32(PLVD):
                PLVD.Read(buffer, subSize);
                break;
            case REV32(CTDA):
                CTDA.Read(buffer, subSize);
                break;
            case REV32(MNAM):
                if(RNAM.value.size() == 0)
                    RNAM.value.push_back(new FACTRNAM);
                RNAM.value.back()->MNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(FNAM):
                if(RNAM.value.size() == 0)
                    RNAM.value.push_back(new FACTRNAM);
                RNAM.value.back()->FNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(CITC):
            case REV32(CIS2):
                CBASH_SUBTYPE_NOT_IMPLEMENTED
                buffer += subSize;
                break;
            default:
                CBASH_SUBTYPE_UNKNOWN
                CBASH_CHUNK_DEBUG
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t FACTRecord::Unload()
    {
        IsChanged(false);
        IsLoaded(false);
        EDID.Unload();
        FULL.Unload();
        XNAM.Unload();
        DATA.Unload();
        JAIL.Unload();
        WAIT.Unload();
        STOL.Unload();
        PLCN.Unload();
        CRGR.Unload();
        JOUT.Unload();
        JAIL.Unload();
        CRVA.Unload();
        RNAM.Unload();
        VEND.Unload();
        VENC.Unload();
        VENV.Unload();
        PLVD.Unload();
        CTDA.Unload();
        return 1;
    }

int32_t FACTRecord::WriteRecord(FileWriter &writer)
{
    WRITE(EDID);
    WRITE(FULL);
    WRITE(XNAM);
    WRITE(DATA);
    WRITE(JAIL);
    WRITE(WAIT);
    WRITE(STOL);
    WRITE(PLCN);
    WRITE(CRGR);
    WRITE(JOUT);
    WRITE(JAIL);
    WRITE(CRVA);
    WRITE(RNAM);
    WRITE(VEND);
    WRITE(VENC);
    WRITE(VENV);
    WRITE(PLVD);
    WRITE(CTDA);
    return -1;
}

    bool FACTRecord::operator ==(const FACTRecord &other) const
    {
        return (EDID.equalsi(other.EDID) &&
            FULL.equalsi(other.FULL) &&
            XNAM == other.XNAM &&
            DATA == other.DATA &&
            JAIL == other.JAIL &&
            WAIT == other.WAIT &&
            STOL == other.STOL &&
            PLCN == other.PLCN &&
            CRGR == other.CRGR &&
            JOUT == other.JOUT &&
            JAIL == other.JAIL &&
            CRVA == other.CRVA &&
            RNAM == other.RNAM &&
            VEND == other.VEND &&
            VENC == other.VENC &&
            VENV == other.VENV &&
            PLVD == other.PLVD &&
            CTDA == other.CTDA);
    }

bool FACTRecord::operator !=(const FACTRecord &other) const
    {
    return !(*this == other);
    }

bool FACTRecord::equals(Record *other)
    {
    return *this == *(FACTRecord *)other;
    }
}