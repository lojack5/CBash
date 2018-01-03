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
*  Jacob "Lojack" Lojewski
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
#include "../../ModFile.h"
#include "NPC_Record.h"

namespace Sk {
    NPC_Record::NPC_Record(unsigned char *_recData):
        TES5Record(_recData)
    {
        //
    }

    NPC_Record::NPC_Record(NPC_Record *srcRecord) :
        TES5Record(srcRecord)
    {
        if (srcRecord == NULL || !srcRecord->IsChanged())
            return;

        EDID = srcRecord->EDID;
        VMAD = srcRecord->VMAD;
        OBND = srcRecord->OBND;
        ACBS = srcRecord->ACBS;
        SNAM = srcRecord->SNAM;
        INAM = srcRecord->INAM;
        VTCK = srcRecord->VTCK;
        TPLT = srcRecord->TPLT;
        RNAM = srcRecord->RNAM;
        SPLO = srcRecord->SPLO;
        Destructable = srcRecord->Destructable;
        WNAM = srcRecord->WNAM;
        ANAM = srcRecord->ANAM;
        ATKR = srcRecord->ATKR;
        attacks = srcRecord->attacks;
        SPOR = srcRecord->SPOR;
        OCOR = srcRecord->OCOR;
        GWOR = srcRecord->GWOR;
        ECOR = srcRecord->ECOR;
        PRKR = srcRecord->PRKR;
        CNTO = srcRecord->CNTO;
        AIDT = srcRecord->AIDT;
        PKID = srcRecord->PKID;
        KWDA = srcRecord->KWDA;
        CNAM = srcRecord->CNAM;
        FULL = srcRecord->FULL;
        SHRT = srcRecord->SHRT;
        DNAM = srcRecord->DNAM;
        PNAM = srcRecord->PNAM;
        HCLF = srcRecord->HCLF;
        ZNAM = srcRecord->ZNAM;
        GNAM = srcRecord->GNAM;
        NAM5 = srcRecord->NAM5;
        NAM6 = srcRecord->NAM6;
        NAM7 = srcRecord->NAM7;
        NAM8 = srcRecord->NAM8;
        CSDT = srcRecord->CSDT;
        CSCR = srcRecord->CSCR;
        DOFT = srcRecord->DOFT;
        SOFT = srcRecord->SOFT;
        DPLT = srcRecord->DPLT;
        CRIF = srcRecord->CRIF;
        FTST = srcRecord->FTST;
        QNAM = srcRecord->QNAM;
        NAM9 = srcRecord->NAM9;
        NAMA = srcRecord->NAMA;
        TintLayers = srcRecord->TintLayers;

    }

    NPC_Record::~NPC_Record()
    {
        //
    }

    bool NPC_Record::VisitFormIDs(FormIDOp &op)
    {
        if (!IsLoaded())    // should this be here? ALCH & LVLI disagree
            return false;

        if (SNAM.IsLoaded())
        {
            for(uint32_t it = 0; it < SNAM.value.size(); ++it)
            {
                op.Accept(SNAM.value[it]->faction);
            }
        }

        if (INAM.IsLoaded())
        {
            op.Accept(INAM.value);
        }
        if (VTCK.IsLoaded() ) { 
			op.Accept(VTCK.value ); 
		}
        if (TPLT.IsLoaded() ) { 
			op.Accept(TPLT.value ); 
		}
        if (RNAM.IsLoaded() ) { 
			op.Accept(RNAM.value ); 
		}

        for (uint32_t x = 0; x < SPLO.value.size(); ++x)
            op.Accept(SPLO.value[x]);

        if (Destructable.IsLoaded()) {
            Destructable->VisitFormIDs(op);
        }

        if (WNAM.IsLoaded() ) { 
			op.Accept(WNAM.value ); 
		}
        if (ANAM.IsLoaded() ) { 
			op.Accept(ANAM.value ); 
		} 
        if (ATKR.IsLoaded() ) { 
			op.Accept(ATKR.value ); 
		}

        if (attacks.IsLoaded())
        {
			for (uint32_t it = 0; it < attacks.value.size(); ++it)
            {
				GENATTACK *attk = attacks.value[it];
                op.Accept(attk->ATKD.value.attackSpell);
                op.Accept(attk->ATKD.value.attackType);
            }
        }

        if (SPOR.IsLoaded() ) { 
			op.Accept(SPOR.value ); 
		}
		if (OCOR.IsLoaded() ) { 
			op.Accept(OCOR.value ); 
		}
		if (GWOR.IsLoaded() ) { 
			op.Accept(GWOR.value ); 
		}
		if (ECOR.IsLoaded() ) { 
			op.Accept(ECOR.value ); 
		}

        if (PRKR.IsLoaded())
        {
			for (uint32_t it = 0; it < PRKR.value.size(); ++it)
            {
                op.Accept(PRKR.value[it]->perk);
            }
        }

        if (CNTO.IsLoaded())
        {
			for (uint32_t it = 0; it < CNTO.value.size(); ++it)
			{
                op.Accept(CNTO.value[it]->item);
            }
        }

        if (PKID.IsLoaded())
        {
			for (uint32_t it = 0; it < PKID.value.size(); ++it)
			{
                op.Accept(PKID.value[it]);
            }
        }

        if (KWDA.IsLoaded())
        {
			for (uint32_t it = 0; it < KWDA.value.size(); ++it)
			{
                op.Accept(KWDA.value[it]);
            }
        }

        if (CNAM.IsLoaded() ) { 
			op.Accept(CNAM.value ); 
		}

        if (PNAM.IsLoaded())
        {
			for (uint32_t it = 0; it < PNAM.value.size(); ++it)
            {
                op.Accept(PNAM.value[it]);
            }
        }

        if (HCLF.IsLoaded() ) { 
			op.Accept(HCLF.value ); 
		}
				
		if (ZNAM.IsLoaded() ) { 
			op.Accept(ZNAM.value ); 
		}
		
		if (GNAM.IsLoaded() ) { 
			op.Accept(GNAM.value ); 
		}

        if (CSDT.IsLoaded())
        {
			for (uint32_t it = 0; it < CSDT.value.size(); ++it)
            {
				SOUNDPACK* csdt = CSDT.value[it];
				for (uint32_t ik = 0; ik < csdt->sounds.value.size(); ++ik)
                {					
                    op.Accept(csdt->sounds.value[ik]->CSDI.value);
                }                
            }
        }

        if (CSCR.IsLoaded() ) { 
			op.Accept(CSCR.value ); 
		}
        if (DOFT.IsLoaded() ) { 
			op.Accept(DOFT.value ); 
		}
        if (SOFT.IsLoaded() ) { 
			op.Accept(SOFT.value ); 
		}
        if (DPLT.IsLoaded() ) { 
			op.Accept(DPLT.value ); 
		}
        if (CRIF.IsLoaded() ) { 
			op.Accept(CRIF.value ); 
		}
        if (FTST.IsLoaded() ) { 
			op.Accept(FTST.value ); 
		}

        return op.Stop();
    }

    bool NPC_Record::IsFemale()
    {
        return (ACBS.value.flags & fFemale);
    }
    void NPC_Record::IsFemale(bool value)
    {
        SETBIT(ACBS.value.flags, fFemale, value);
    }

    bool NPC_Record::IsEssential()
    {
        return (ACBS.value.flags & fEssential);
    }
    void NPC_Record::IsEssential(bool value)
    {
        SETBIT(ACBS.value.flags, fEssential, value);
    }

    bool NPC_Record::IsIsCharGenFacePreset()
    {
        return (ACBS.value.flags & fIsCharGenFacePreset);
    }
    void NPC_Record::IsIsCharGenFacePreset(bool value)
    {
        SETBIT(ACBS.value.flags, fIsCharGenFacePreset, value);
    }

    bool NPC_Record::IsRespawn()
    {
        return (ACBS.value.flags & fRespawn);
    }
    void NPC_Record::IsRespawn(bool value)
    {
        SETBIT(ACBS.value.flags, fRespawn, value);
    }

    bool NPC_Record::IsAutocalcStats()
    {
        return (ACBS.value.flags & fAutocalcStats);
    }
    void NPC_Record::IsAutocalcStats(bool value)
    {
        SETBIT(ACBS.value.flags, fAutocalcStats, value);
    }

    bool NPC_Record::IsUnique()
    {
        return (ACBS.value.flags & fUnique);
    }
    void NPC_Record::IsUnique(bool value)
    {
        SETBIT(ACBS.value.flags, fUnique, value);
    }

    bool NPC_Record::IsDoesntAffectStealthMeter()
    {
        return (ACBS.value.flags & fDoesntAffectStealthMeter);
    }
    void NPC_Record::IsDoesntAffectStealthMeter(bool value)
    {
        SETBIT(ACBS.value.flags, fDoesntAffectStealthMeter, value);
    }

    bool NPC_Record::IsPCLevelMult()
    {
        return (ACBS.value.flags & fPCLevelMult);
    }
    void NPC_Record::IsPCLevelMult(bool value)
    {
        SETBIT(ACBS.value.flags, fPCLevelMult, value);
    }

    bool NPC_Record::IsUseTemplate()
    {
        return (ACBS.value.flags & fUseTemplate);
    }
    void NPC_Record::IsUseTemplate(bool value)
    {
        SETBIT(ACBS.value.flags, fUseTemplate, value);
    }

    bool NPC_Record::IsUnknown9()
    {
        return (ACBS.value.flags & fUnknown9);
    }
    void NPC_Record::IsUnknown9(bool value)
    {
        SETBIT(ACBS.value.flags, fUnknown9, value);
    }

    bool NPC_Record::IsUnknown10()
    {
        return (ACBS.value.flags & fUnknown10);
    }
    void NPC_Record::IsUnknown10(bool value)
    {
        SETBIT(ACBS.value.flags, fUnknown10, value);
    }

    bool NPC_Record::IsProtected()
    {
        return (ACBS.value.flags & fProtected);
    }
    void NPC_Record::IsProtected(bool value)
    {
        SETBIT(ACBS.value.flags, fProtected, value);
    }

    bool NPC_Record::IsUnknown12()
    {
        return (ACBS.value.flags & fUnknown12);
    }
    void NPC_Record::IsUnknown12(bool value)
    {
        SETBIT(ACBS.value.flags, fUnknown12, value);
    }

    bool NPC_Record::IsUnknown13()
    {
        return (ACBS.value.flags & fUnknown13);
    }
    void NPC_Record::IsUnknown13(bool value)
    {
        SETBIT(ACBS.value.flags, fUnknown13, value);
    }

    bool NPC_Record::IsSummonable()
    {
        return (ACBS.value.flags & fSummonable);
    }
    void NPC_Record::IsSummonable(bool value)
    {
        SETBIT(ACBS.value.flags, fSummonable, value);
    }

    bool NPC_Record::IsUnknown15()
    {
        return (ACBS.value.flags & fUnknown15);
    }
    void NPC_Record::IsUnknown15(bool value)
    {
        SETBIT(ACBS.value.flags, fUnknown15, value);
    }

    bool NPC_Record::IsDoesntBleed()
    {
        return (ACBS.value.flags & fDoesntBleed);
    }
    void NPC_Record::IsDoesntBleed(bool value)
    {
        SETBIT(ACBS.value.flags, fDoesntBleed, value);
    }

    bool NPC_Record::IsUnknown17()
    {
        return (ACBS.value.flags & fUnknown17);
    }
    void NPC_Record::IsUnknown17(bool value)
    {
        SETBIT(ACBS.value.flags, fUnknown17, value);
    }

    bool NPC_Record::IsBleedoutOverride()
    {
        return (ACBS.value.flags & fBleedoutOverride);
    }
    void NPC_Record::IsBleedoutOverride(bool value)
    {
        SETBIT(ACBS.value.flags, fBleedoutOverride, value);
    }

    bool NPC_Record::IsOppositeGenderAnims()
    {
        return (ACBS.value.flags & fOppositeGenderAnims);
    }
    void NPC_Record::IsOppositeGenderAnims(bool value)
    {
        SETBIT(ACBS.value.flags, fOppositeGenderAnims, value);
    }

    bool NPC_Record::IsSimpleActor()
    {
        return (ACBS.value.flags & fSimpleActor);
    }
    void NPC_Record::IsSimpleActor(bool value)
    {
        SETBIT(ACBS.value.flags, fSimpleActor, value);
    }

    bool NPC_Record::IsLoopedscript()
    {
        return (ACBS.value.flags & fLoopedscript);
    }
    void NPC_Record::IsLoopedscript(bool value)
    {
        SETBIT(ACBS.value.flags, fLoopedscript, value);
    }

    bool NPC_Record::IsUnknown22()
    {
        return (ACBS.value.flags & fUnknown22);
    }
    void NPC_Record::IsUnknown22(bool value)
    {
        SETBIT(ACBS.value.flags, fUnknown22, value);
    }

    bool NPC_Record::IsUnknown23()
    {
        return (ACBS.value.flags & fUnknown23);
    }
    void NPC_Record::IsUnknown23(bool value)
    {
        SETBIT(ACBS.value.flags, fUnknown23, value);
    }

    bool NPC_Record::IsUnknown24()
    {
        return (ACBS.value.flags & fUnknown24);
    }
    void NPC_Record::IsUnknown24(bool value)
    {
        SETBIT(ACBS.value.flags, fUnknown24, value);
    }

    bool NPC_Record::IsUnknown25()
    {
        return (ACBS.value.flags & fUnknown25);
    }
    void NPC_Record::IsUnknown25(bool value)
    {
        SETBIT(ACBS.value.flags, fUnknown25, value);
    }

    bool NPC_Record::IsUnknown26()
    {
        return (ACBS.value.flags & fUnknown26);
    }
    void NPC_Record::IsUnknown26(bool value)
    {
        SETBIT(ACBS.value.flags, fUnknown26, value);
    }

    bool NPC_Record::IsUnknown27()
    {
        return (ACBS.value.flags & fUnknown27);
    }
    void NPC_Record::IsUnknown27(bool value)
    {
        SETBIT(ACBS.value.flags, fUnknown27, value);
    }

    bool NPC_Record::IsLoopedAudio()
    {
        return (ACBS.value.flags & fLoopedAudio);
    }
    void NPC_Record::IsLoopedAudio(bool value)
    {
        SETBIT(ACBS.value.flags, fLoopedAudio, value);
    }

    bool NPC_Record::IsIsGhost()
    {
        return (ACBS.value.flags & fIsGhost);
    }
    void NPC_Record::IsIsGhost(bool value)
    {
        SETBIT(ACBS.value.flags, fIsGhost, value);
    }

    bool NPC_Record::IsUnknown30()
    {
        return (ACBS.value.flags & fUnknown30);
    }
    void NPC_Record::IsUnknown30(bool value)
    {
        SETBIT(ACBS.value.flags, fUnknown30, value);
    }

    bool NPC_Record::IsInvulnerable()
    {
        return (ACBS.value.flags & fInvulnerable);
    }
    void NPC_Record::IsInvulnerable(bool value)
    {
        SETBIT(ACBS.value.flags, fInvulnerable, value);
    }

    bool NPC_Record::IsFlagMask(uint32_t Mask, bool Exact) const
    {
        return Exact ? ((ACBS.value.flags & Mask) == Mask) : ((ACBS.value.flags & Mask) != 0);
    }

    void NPC_Record::SetFlagMask(uint32_t Mask)
    {
        ACBS.value.flags = Mask;
    }

    uint32_t NPC_Record::GetType()
    {
        return REV32(NPC_);
    }

    char * NPC_Record::GetStrType()
    {
        return "NPC_";
    }

    int32_t NPC_Record::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
        uint32_t subType = 0;
        uint32_t subSize = 0;
        StringLookups *LookupStrings = GetParentMod()->TES4.LookupStrings;
        while (buffer < end_buffer)
        {
            subType = *(uint32_t *)buffer;
            buffer += 4;
            switch (subType)
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
            switch (subType)
            {
            case REV32(EDID):
                EDID.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(VMAD):
                VMAD.Read(buffer, subSize, GetType(), CompressedOnDisk);
                break;
            case REV32(OBND):
                OBND.Read(buffer, subSize);
                break;
            case REV32(ACBS):
                ACBS.Read(buffer, subSize);
                break;
            case REV32(SNAM):
                SNAM.Read(buffer, subSize);
                break;
            case REV32(INAM):
                INAM.Read(buffer, subSize);
                break;
            case REV32(VTCK):
                VTCK.Read(buffer, subSize);
                break;
            case REV32(TPLT):
                TPLT.Read(buffer, subSize);
                break;
            case REV32(RNAM):
                RNAM.Read(buffer, subSize);
                break;
            case REV32(SPCT):
                // Number of SPLOs
                buffer += subSize;
                break;
            case REV32(SPLO):
                SPLO.Read(buffer, subSize);
                break;
            case REV32(DEST):
                Destructable.Load();
                Destructable->DEST.Read(buffer, subSize);
                break;
            case REV32(DSTD):
                Destructable.Load();
                Destructable->Stages.value.push_back(new SKDESTSTAGE);
                Destructable->Stages.value.back()->DSTD.Read(buffer, subSize);
                break;
            case REV32(DMDL):
                Destructable.Load();
                if (Destructable->Stages.value.size() == 0)
                    Destructable->Stages.value.push_back(new SKDESTSTAGE);
                Destructable->Stages.value.back()->DMDL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DMDT):
                Destructable.Load();
                if (Destructable->Stages.value.size() == 0)
                    Destructable->Stages.value.push_back(new SKDESTSTAGE);
                Destructable->Stages.value.back()->DMDT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DMDS):
                Destructable.Load();
                if (Destructable->Stages.value.size() == 0)
                    Destructable->Stages.value.push_back(new SKDESTSTAGE);
                Destructable->Stages.value.back()->DMDS.Read(buffer, subSize);
                break;
            case REV32(DSTF):
                //Marks end of a destruction stage
                buffer += subSize;
                break;
            case REV32(WNAM):
                WNAM.Read(buffer, subSize);
                break;
            case REV32(ANAM):
                ANAM.Read(buffer, subSize);
                break;
            case REV32(ATKR):
                ATKR.Read(buffer, subSize);
                break;
            case REV32(ATKD): // attack package
                attacks.value.push_back(new GENATTACK);
                attacks.value.back()->ATKD.Read(buffer, subSize);
                break;
            case REV32(ATKE):
                if (attacks.value.size() == 0)
                    attacks.value.push_back(new GENATTACK); // should also report bad data
                attacks.value.back()->ATKE.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SPOR):
                SPOR.Read(buffer, subSize);
                break;
            case REV32(OCOR):
                OCOR.Read(buffer, subSize);
                break;
            case REV32(GWOR):
                GWOR.Read(buffer, subSize);
                break;
            case REV32(ECOR):
                ECOR.Read(buffer, subSize);
                break;
            case REV32(PRKZ):
                // number of PRKR
                buffer += subSize;
                break;
            case REV32(PRKR):
                PRKR.Read(buffer, subSize);
                break;
            case REV32(COCT):
                // number of CNTO
                buffer += subSize;
                break;
            case REV32(CNTO):
                CNTO.Read(buffer, subSize);
                break;
            case REV32(AIDT):
                AIDT.Read(buffer, subSize);
                break;
            case REV32(PKID):
                PKID.Read(buffer, subSize);
                break;
            case REV32(KSIZ):
                // number of KWDA
                buffer += subSize;
                break;
            case REV32(KWDA):
                KWDA.Read(buffer, subSize);
                break;
            case REV32(CNAM):
                CNAM.Read(buffer, subSize);
                break;
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk, LookupStrings);
                break;
            case REV32(SHRT):
                SHRT.Read(buffer, subSize, CompressedOnDisk, LookupStrings);
                break;
            case REV32(DATA):
                // zero size
                buffer += subSize;
                break;
            case REV32(DNAM):
                DNAM.Read(buffer, subSize);
                break;
            case REV32(PNAM):
                PNAM.Read(buffer, subSize);
                break;
            case REV32(HCLF):
                HCLF.Read(buffer, subSize);
                break;
            case REV32(ZNAM):
                ZNAM.Read(buffer, subSize);
                break;
            case REV32(GNAM):
                GNAM.Read(buffer, subSize);
                break;
            case REV32(NAM5):
                NAM5.Read(buffer, subSize);
                break;
            case REV32(NAM6):
                NAM6.Read(buffer, subSize);
                break;
            case REV32(NAM7):
                NAM7.Read(buffer, subSize);
                break;
            case REV32(NAM8):
                NAM8.Read(buffer, subSize);
                break;
            case REV32(CSDT):
                CSDT.value.push_back(new SOUNDPACK);
                CSDT.value.back()->soundLocation.Read(buffer, subSize);
                break;
            case REV32(CSDI):
                if (CSDT.value.size() == 0)
                    CSDT.value.push_back(new SOUNDPACK); // report format error
                if (CSDT.value.back()->sounds.value.size() == 0)
                    CSDT.value.back()->sounds.value.push_back(new SOUNDPAIR); // report format error
                CSDT.value.back()->sounds.value.back()->CSDI.Read(buffer, subSize);
                break;
            case REV32(CSDC):
                if (CSDT.value.size() == 0)
                    CSDT.value.push_back(new SOUNDPACK); // report format error
                if (CSDT.value.back()->sounds.value.size() == 0)
                    CSDT.value.back()->sounds.value.push_back(new SOUNDPAIR); // report format error
                CSDT.value.back()->sounds.value.back()->CSDC.Read(buffer, subSize);
                break;
            case REV32(CSCR):
                CSCR.Read(buffer, subSize);
                break;
            case REV32(DOFT):
                DOFT.Read(buffer, subSize);
                break;
            case REV32(SOFT):
                SOFT.Read(buffer, subSize);
                break;
            case REV32(DPLT):
                DPLT.Read(buffer, subSize);
                break;
            case REV32(CRIF):
                CRIF.Read(buffer, subSize);
                break;
            case REV32(FTST):
                FTST.Read(buffer, subSize);
                break;
            case REV32(QNAM):
                QNAM.Read(buffer, subSize);
                break;
            case REV32(NAM9):
                NAM9.Read(buffer, subSize);
                break;
			case REV32(NAMA):
				NAMA.Read(buffer, subSize);
				break;
            case REV32(TINI):
                TintLayers.value.push_back(new TINTLAYER);
                TintLayers.value.back()->TINI.Read(buffer, subSize);
                break;
            case REV32(TINC):
                if (TintLayers.value.size() == 0)
                    TintLayers.value.push_back(new TINTLAYER); // report format error
                TintLayers.value.back()->TINC.Read(buffer, subSize);
                break;
            case REV32(TINV):
                if (TintLayers.value.size() == 0)
                    TintLayers.value.push_back(new TINTLAYER); // report format error
                TintLayers.value.back()->TINV.Read(buffer, subSize);
                break;
            case REV32(TIAS):
                if (TintLayers.value.size() == 0)
                    TintLayers.value.push_back(new TINTLAYER); // report format error
                TintLayers.value.back()->TIAS.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  NPC_: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                    printer("  Size = %i\n", subSize);
                printer("  CurPos = %08x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
        return 0;
    }

    int32_t NPC_Record::Unload()
    {
        IsChanged(false);
        IsLoaded(false);
        

        return 1;
    }

    int32_t NPC_Record::WriteRecord(FileWriter &writer)
    {
        WRITE(EDID);
        WRITE(VMAD);
        WRITE(OBND);
        WRITE(ACBS);
        WRITE(SNAM);
        WRITE(INAM);
        WRITE(VTCK);
        WRITE(TPLT);
        WRITE(RNAM);
        // SPCT skipped
        WRITE(SPLO);
        Destructable.Write(writer);
        WRITE(WNAM);
        WRITE(ANAM);
        WRITE(ATKR);
        attacks.Write(writer);
        WRITE(SPOR);
        WRITE(OCOR);
        WRITE(GWOR);
        WRITE(ECOR);
        WRITE(PRKR);
        WRITE(CNTO);
        WRITE(AIDT);
        WRITE(PKID);
        WRITE(KWDA);
        WRITE(CNAM);
        WRITE(FULL);
        WRITE(SHRT);
        WRITEEMPTY(DATA);
        WRITE(DNAM);
        WRITE(PNAM);
        WRITE(HCLF);
        WRITE(ZNAM);
        WRITE(GNAM);
        WRITE(NAM5);
        WRITE(NAM6);
        WRITE(NAM7);
        WRITE(NAM8);
        WRITE(CSDT);
        WRITE(CSCR);
        WRITE(DOFT);
        WRITE(SOFT);
        WRITE(DPLT);
        WRITE(CRIF);
        WRITE(FTST);
        WRITE(QNAM);
        WRITE(NAM9);
        WRITE(NAMA);
        TintLayers.Write(writer);
        return -1;
    }

    bool NPC_Record::operator ==(const NPC_Record &other) const
    {
        return (EDID.equalsi(other.EDID) &&
                VMAD == other.VMAD &&
                OBND == other.OBND &&
                ACBS == other.ACBS &&
                SNAM == other.SNAM &&
                INAM == other.INAM &&
                VTCK == other.VTCK &&
                TPLT == other.VTCK &&
                RNAM == other.RNAM &&
                SPLO == other.SPLO &&
                Destructable == other.Destructable &&
                WNAM == other.WNAM &&
                ANAM == other.ANAM &&
                ATKR == other.ATKR &&
                attacks == other.attacks &&
                SPOR == other.SPOR &&
                OCOR == other.OCOR &&
                GWOR == other.GWOR &&
                ECOR == other.ECOR &&
                PRKR == other.PRKR &&
                CNTO == other.CNTO &&
                AIDT == other.AIDT &&
                PKID == other.PKID &&
                KWDA == other.KWDA &&
                CNAM == other.CNAM &&
                FULL.equals(other.FULL) &&
                SHRT.equals(other.SHRT) &&
                DNAM == other.DNAM &&
                PNAM == other.PNAM &&
                HCLF == other.HCLF &&
                ZNAM == other.ZNAM &&
                GNAM == other.GNAM &&
                NAM5 == other.NAM5 &&
                NAM6 == other.NAM6 &&
                NAM7 == other.NAM7 &&
                NAM8 == other.NAM8 &&
                CSDT == other.CSDT &&
                CSCR == other.CSCR &&
                DOFT == other.DOFT &&
                SOFT == other.SOFT &&
                DPLT == other.DPLT &&
                CRIF == other.CRIF &&
                FTST == other.FTST &&
                QNAM == other.QNAM &&
                NAM9 == other.NAM9 &&
                NAMA == other.NAMA &&
                TintLayers == other.TintLayers
                );
    }

    bool NPC_Record::operator != (const NPC_Record &other) const
    {
        return !(*this == other);
    }

    bool NPC_Record::equals(Record *other)
    {
        return *this == *(NPC_Record *)other;
    }

	NPC_Record::SKDNAM::SKDNAM():
		OneHanded(0),
		TwoHanded(0),
		Marksman(0),
		Block(0),
		Smithing(0),
		HeavyArmor(0),
		LightArmor(0),
		Pickpocket(0),
		Lockpicking(0),
		Sneak(0),
		Alchemy(0),
		Speechcraft(0),
		Alteration(0),
		Conjuration(0),
		Destruction(0),
		Illusion(0),
		Restoration(0),
		Enchanting(0),
		OneHandedOff(0),
		TwoHandedOff(0),
		MarksmanOff(0),
		BlockOff(0),
		SmithingOff(0),
		HeavyArmorOff(0),
		LightArmorOff(0),
		PickpocketOff(0),
		LockpickingOff(0),
		SneakOff(0),
		AlchemyOff(0),
		SpeechcraftOff(0),
		AlterationOff(0),
		ConjurationOff(0),
		DestructionOff(0),
		IllusionOff(0),
		RestorationOff(0),
		EnchantingOff(0),
		health(0),
		magicka(0),
		stamina(0),
		unused1(0),
		farAwayModelDistance(0),
		gearedUpWeapons(0)
	{
		memset(&unused2, 0, sizeof(unused2));
	}

	NPC_Record::SKDNAM::~SKDNAM() {

	}
	bool NPC_Record::SKDNAM::operator == (const NPC_Record::SKDNAM &other) const
	{
		return (OneHanded == other.OneHanded &&
			TwoHanded == other.TwoHanded &&
			Marksman == other.Marksman &&
			Block == other.Block &&
			Smithing == other.Smithing &&
			HeavyArmor == other.HeavyArmor &&
			LightArmor == other.LightArmor &&
			Pickpocket == other.Pickpocket &&
			Lockpicking == other.Lockpicking &&
			Sneak == other.Sneak &&
			Alchemy == other.Alchemy &&
			Speechcraft == other.Speechcraft &&
			Alteration == other.Alteration &&
			Conjuration == other.Conjuration &&
			Destruction == other.Destruction &&
			Illusion == other.Illusion &&
			Restoration == other.Restoration &&
			Enchanting == other.Enchanting &&
			OneHandedOff == other.OneHandedOff &&
			TwoHandedOff == other.TwoHandedOff &&
			MarksmanOff == other.MarksmanOff &&
			BlockOff == other.BlockOff &&
			SmithingOff == other.SmithingOff &&
			HeavyArmorOff == other.HeavyArmorOff &&
			LightArmorOff == other.LightArmorOff &&
			PickpocketOff == other.PickpocketOff &&
			LockpickingOff == other.LockpickingOff &&
			SneakOff == other.SneakOff &&
			AlchemyOff == other.AlchemyOff &&
			SpeechcraftOff == other.SpeechcraftOff &&
			AlterationOff == other.AlterationOff &&
			ConjurationOff == other.ConjurationOff &&
			DestructionOff == other.DestructionOff &&
			IllusionOff == other.IllusionOff &&
			RestorationOff == other.RestorationOff &&
			EnchantingOff == other.EnchantingOff &&
			health == other.health &&
			magicka == other.magicka &&
			stamina == other.stamina &&
			farAwayModelDistance == other.farAwayModelDistance &&
			gearedUpWeapons == other.gearedUpWeapons);
	}

	bool NPC_Record::SKDNAM::operator != (const NPC_Record::SKDNAM &other) const
	{
		return !(*this == other);
	}


	bool NPC_Record::SOUNDPACK::operator == (const NPC_Record::SOUNDPACK &other) const
	{
		return (soundLocation == other.soundLocation && sounds == other.sounds);
	}

	bool NPC_Record::SOUNDPACK::operator != (const NPC_Record::SOUNDPACK &other) const
	{
		return !(*this == other);
	}


	bool NPC_Record::SOUNDPAIR::operator == (const NPC_Record::SOUNDPAIR &other) const
	{
		return (CSDI == other.CSDI && CSDC == other.CSDC);
	}

	bool NPC_Record::SOUNDPAIR::operator != (const NPC_Record::SOUNDPAIR &other) const
	{
		return !(*this == other);
	}

	bool NPC_Record::QNAMTRIPLE::operator == (const NPC_Record::QNAMTRIPLE &other) const
	{
		return (red == other.red && green == other.green && blue == other.blue);
	}

	bool NPC_Record::QNAMTRIPLE::operator != (const NPC_Record::QNAMTRIPLE &other) const
	{
		return !(*this == other);
	}

	bool NPC_Record::FACEMORPH::operator == (const NPC_Record::FACEMORPH &other) const
	{
		return (NoseLongShort == other.NoseLongShort &&
			NoseUpDown == other.NoseUpDown &&
			JawUpDown == other.JawUpDown &&
			JawNarrowWide == other.JawNarrowWide &&
			JawFarwardBack == other.JawFarwardBack &&
			CheeksUpDown == other.CheeksUpDown &&
			CheeksFarwardBack == other.CheeksFarwardBack &&
			EyesUpDown == other.EyesUpDown &&
			EyesInOut == other.EyesInOut &&
			BrowsUpDown == other.BrowsUpDown &&
			BrowsInOut == other.BrowsInOut &&
			BrowsFarwardBack == other.BrowsFarwardBack &&
			LipsUpDown == other.LipsUpDown &&
			LipsInOut == other.LipsInOut &&
			ChinNarrowWide == other.ChinNarrowWide &&
			ChinUpDown == other.ChinUpDown &&
			ChinUnderbiteOverbite == other.ChinUnderbiteOverbite &&
			EyesFarwardBack == other.EyesFarwardBack);
	}

	bool NPC_Record::FACEMORPH::operator != (const NPC_Record::FACEMORPH &other) const
	{
		return !(*this == other);
	}

	bool NPC_Record::FACEPARTS::operator == (const NPC_Record::FACEPARTS &other) const
	{
		return (nose == other.nose && mouth == other.mouth && eyes == other.eyes);
	}

	bool NPC_Record::FACEPARTS::operator != (const NPC_Record::FACEPARTS &other) const
	{
		return !(*this == other);
	}

	bool NPC_Record::TINTLAYER::operator == (const NPC_Record::TINTLAYER &other) const
	{
		return (TINI == other.TINI && TINC == other.TINC && TINV == other.TINV && TIAS == other.TIAS);
	}

	bool NPC_Record::TINTLAYER::operator != (const NPC_Record::TINTLAYER &other) const
	{
		return !(*this == other);
	}

	void NPC_Record::TINTLAYER::Write(FileWriter &writer)
	{
		WRITE(TINI);
		WRITE(TINC);
		WRITE(TINV);
		WRITE(TIAS);
	}

	NPC_Record::TINTLAYER::TINTCOLORS::TINTCOLORS() :
		red(0),
		green(0),
		blue(0)
	{
		//..
	}

	NPC_Record::TINTLAYER::TINTCOLORS::~TINTCOLORS() {

	}

	bool NPC_Record::TINTLAYER::TINTCOLORS::operator == (const NPC_Record::TINTLAYER::TINTCOLORS &other) const
	{
		return (red == other.red && green == other.green && blue == other.blue && alpha == other.alpha);
	}

	bool NPC_Record::TINTLAYER::TINTCOLORS::operator != (const NPC_Record::TINTLAYER::TINTCOLORS &other) const
	{
		return !(*this == other);
	}

	NPC_Record::SKAIDT::SKAIDT() :
		aggression(0) {

	}

	NPC_Record::SKAIDT::~SKAIDT() {

	}

	bool NPC_Record::SKAIDT::operator == (const NPC_Record::SKAIDT &other) const
	{
		return (aggression == other.aggression &&
			confidence == other.confidence &&
			energyLevel == other.energyLevel &&
			responsibility == other.responsibility &&
			mood == other.mood &&
			assistance == other.assistance &&
			agroRadiusBehavior == other.agroRadiusBehavior &&
			warn == other.warn &&
			warnAttack == other.warnAttack &&
			attack == other.attack
			);
	}

	bool NPC_Record::SKAIDT::operator != (const NPC_Record::SKAIDT &other) const
	{
		return !(*this == other);
	}

} // namespace Sk