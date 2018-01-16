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
#include "REFRRecord.h"

namespace Sk
{
    REFRRecord::REFRRecord(unsigned char *_recData) :
        TES5Record(_recData)
    {
        //
    }

    REFRRecord::REFRRecord(REFRRecord *srcRecord) :
        TES5Record()
    {
        if (srcRecord == NULL)
            return;

        EDID = srcRecord->EDID; //Editor ID
        VMAD = srcRecord->VMAD;
        NAME = srcRecord->NAME;
        XMBO = srcRecord->XMBO;
        XPRM = srcRecord->XPRM; //Primitive
        XPOD = srcRecord->XPOD; //Portal Data
        Room = srcRecord->Room; //Room Data
        LNAM = srcRecord->LNAM; //Light Inherit Flags
        INAM = srcRecord->INAM; //Light Inherit Flags
        XRGD = srcRecord->XRGD; //Ragdoll Data
        XRDS = srcRecord->XRDS; //Radius
        XEMI = srcRecord->XEMI;
        XLIG = srcRecord->XLIG;
        XESP = srcRecord->XESP;
        XALP = srcRecord->XALP;
        XNDP = srcRecord->XNDP;
        XTEL = srcRecord->XTEL;
        XSCL = srcRecord->XSCL;
        XAPD = srcRecord->XAPD;
        XAPR = srcRecord->XAPR;
        XLIB = srcRecord->XLIB;
        XLKR = srcRecord->XLKR;
        XLOC = srcRecord->XLOC;
        XLRT = srcRecord->XLRT;
        XOWN = srcRecord->XOWN;
        XRNK = srcRecord->XRNK;
        XCNT = srcRecord->XCNT;
        XCVL = srcRecord->XCVL;
        XCVR = srcRecord->XCVR;
        XCZA = srcRecord->XCZA;
        XCZC = srcRecord->XCZC;
        XEZN = srcRecord->XEZN;
        XFVC = srcRecord->XFVC;
        FNAM = srcRecord->FNAM;
        FULL = srcRecord->FULL;
        TNAM = srcRecord->TNAM;
        XHTW = srcRecord->XHTW;
        //XIS2
        XLCM = srcRecord->XLCM;
        XMBR = srcRecord->XMBR;
        XMRK = srcRecord->XMRK;
        //XOCP
        XPWR = srcRecord->XPWR;
        XTRI = srcRecord->XTRI;
        openByDefault = srcRecord->openByDefault;
        XACT = srcRecord->XACT;
        XATR = srcRecord->XATR;
        XWCU = srcRecord->XWCU;
        DATA = srcRecord->DATA; //Position/Rotation
        XTNM = srcRecord->XTNM;
        XIS2 = srcRecord->XIS2;
        XWCN = srcRecord->XWCN;

        XPRD = srcRecord->XPRD;

        if (!srcRecord->IsChanged())
            return;

        return;
    }

    REFRRecord::~REFRRecord()
    {
        //
    }

    uint32_t REFRRecord::GetType()
    {
        return REV32(REFR);
    }

    char * REFRRecord::GetStrType()
    {
        return "REFR";
    }


    bool REFRRecord::VisitFormIDs(FormIDOp &op)
    {
        if (!IsLoaded())
            return false;
        //REVERT ASAP
        op.Accept(NAME.value);
        if (XPOD.IsLoaded()) {
            op.Accept(XPOD.value->room1);
            op.Accept(XPOD.value->room2);
        }

        if (LNAM.IsLoaded()) {
            op.Accept(LNAM.value);
        }

        if (INAM.IsLoaded()) {
            op.Accept(INAM.value);
        }

        if (Room.IsLoaded()) {
            for (uint32_t i = 0; i < Room.value->XLRM.value.size(); ++i) {
                op.Accept(Room.value->XLRM.value[i]);
            }
        }

        if (XEMI.IsLoaded()) {
            op.Accept(XEMI.value);
        }

        if (XESP.IsLoaded()) {
            op.Accept(XESP.value->parent);
        }

        if (XNDP.IsLoaded()) {
            op.Accept(XNDP.value->navMesh);
        }

        if (XTEL.IsLoaded()) {
            op.Accept(XTEL.value->destinationFid);
        }

        if (XAPR.IsLoaded()) {
            op.Accept(XAPR.value->reference);
        }

        if (XLIB.IsLoaded()) {
            op.Accept(XLIB.value);
        }

        if (XLKR.IsLoaded()) {
            op.Accept(XLKR.value->kywd);
            op.Accept(XLKR.value->formid);
        }

        if (XLOC.IsLoaded()) {
            op.Accept(XLOC.value->key);
        }

        if (XLRT.IsLoaded()) {
            for (uint32_t i = 0; i < XLRT.value.size(); ++i) {
                op.Accept(XLRT.value[i]);
            }
        }

        if (XOWN.IsLoaded()) {
            op.Accept(XOWN.value);
        }

        if (XEZN.IsLoaded()) {
            op.Accept(XEZN.value);
        }

        if (XMBR.IsLoaded()) {
            op.Accept(XMBR.value);
        }

        if (XPWR.IsLoaded()) {
            for (uint32_t i = 0; i < XPWR.value.size(); ++i) {
                op.Accept(XPWR.value[i]);
            }
        }

        if (XATR.IsLoaded()) {
            op.Accept(XATR.value);
        }

        return op.Stop();
    }


    int32_t REFRRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
        uint32_t subType = 0;
        uint32_t subSize = 0;
        while (buffer < end_buffer){
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
                VMAD.Load();
                VMAD.value->Read(buffer, subSize, REV32(REFR), CompressedOnDisk);
                break;

            case REV32(NAME):
                NAME.Read(buffer, subSize);
                break;

            case REV32(XMBO):
                XMBO.Read(buffer, subSize);
                break;

            case REV32(XPRM):
                XPRM.Read(buffer, subSize);
                break;

            case REV32(XPOD):
                XPOD.Read(buffer, subSize);
                break;

            case REV32(XLRM):
                Room.Load();
                Room.value->XLRM.Read(buffer, subSize);
                break;

            case REV32(XRMR):
                Room.Load();
                Room.value->XRMR.Read(buffer, subSize);
                break;

            case REV32(LNAM):
                LNAM.Read(buffer, subSize);
                break;

            case REV32(INAM):
                INAM.Read(buffer, subSize);
                break;

            case REV32(XRGD):
                XRGD.Read(buffer, subSize, CompressedOnDisk);
                break;

            case REV32(XRDS):
                XRDS.Read(buffer, subSize);
                break;

            case REV32(XEMI):
                XEMI.Read(buffer, subSize);
                break;

            case REV32(XLIG):
                XLIG.Read(buffer, subSize);
                break;

            case REV32(XESP):
                XESP.Read(buffer, subSize);
                break;

            case REV32(XALP):
                XALP.Read(buffer, subSize);
                break;

            case REV32(XNDP):
                XNDP.Read(buffer, subSize);
                break;

            case REV32(XTEL):
                XTEL.Read(buffer, subSize);
                break;

            case REV32(XSCL):
                XSCL.Read(buffer, subSize);
                break;

            case REV32(XAPD):
                XAPD.Read(buffer, subSize);
                break;

            case REV32(XAPR):
                XAPR.Read(buffer, subSize);
                break;

            case REV32(XLIB):
                XLIB.Read(buffer, subSize);
                break;

            case REV32(XLKR):
                XLKR.Read(buffer, subSize);
                break;

            case REV32(XLOC):
                XLOC.Read(buffer, subSize);
                break;

            case REV32(XLRT):
                XLRT.Read(buffer, subSize);
                break;

            case REV32(XOWN):
                XOWN.Read(buffer, subSize);
                break;
            
            case REV32(XRNK):
                XRNK.Read(buffer, subSize);
                break;

            case REV32(XCNT):
                XCNT.Read(buffer, subSize);
                break;

            case REV32(XCVL):
                XCVL.Read(buffer, subSize);
                break;

            case REV32(XCVR):
                XCVR.Read(buffer, subSize);
                break;

            case REV32(XCZA):
                XCZA.Read(buffer, subSize);
                break;

            case REV32(XCZC):
                XCZC.Read(buffer, subSize);
                break;

            case REV32(XEZN):
                XEZN.Read(buffer, subSize);
                break;

            case REV32(XFVC):
                XFVC.Read(buffer, subSize);
                break;

            case REV32(FNAM):
                FNAM.Read(buffer, subSize);
                break;

            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
                break;

            case REV32(TNAM):
                TNAM.Read(buffer, subSize);
                break;

            case REV32(XHTW):
                XHTW.Read(buffer, subSize);
                break;

            case REV32(ONAM):
                openByDefault = true;
                break;


            case REV32(XLCM):
                XLCM.Read(buffer, subSize);
                break;

            case REV32(XMBR):
                XMBR.Read(buffer, subSize);
                break;


            case REV32(XPWR):
                XPWR.Read(buffer, subSize);
                break;

            case REV32(XTRI):
                XTRI.Read(buffer, subSize);
                break;


            case REV32(XACT):
                XACT.Read(buffer, subSize);
                break;

            case REV32(XATR):
                XATR.Read(buffer, subSize);
                break;

            case REV32(XWCU):
                XWCU.Read(buffer, subSize);
                break;

            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;

            case REV32(XMRK):
                XMRK.Read(buffer, subSize, CompressedOnDisk);
                break;

            case REV32(XTNM):
                XTNM.Read(buffer, subSize);
                break;

            case REV32(XIS2):
                XIS2.Read(buffer, subSize, CompressedOnDisk);
                break;

            case REV32(XWCN):
                XWCN.Read(buffer, subSize);
                break;

            case REV32(XPRD):
                XPRD.Read(buffer, subSize);
                break;

            case REV32(XPPA):
                //Marker
                buffer += subSize;
                break;

            case REV32(PDTO):
                //Not reversed, @TODO add to the code
                buffer += subSize;
                break;

            case REV32(XSPC):
            case REV32(XMBP):
            case REV32(XOCP):
            case REV32(XRGB):
            case REV32(SCHR):
            case REV32(XLCN):
            case REV32(XLTW):
                CBASH_SUBTYPE_NOT_IMPLEMENTED
                buffer = end_buffer;
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

    int32_t REFRRecord::Unload()
    {
        IsChanged(false);
        IsLoaded(false);
        EDID.Unload();
        VMAD.Unload();
        NAME.Unload();
        XMBO.Unload();
        XPRM.Unload();
        XPOD.Unload();
        Room.Unload();
        LNAM.Unload();
        INAM.Unload();
        XRGD.Unload();
        XRDS.Unload();
        XEMI.Unload();
        XLIG.Unload();
        XESP.Unload();
        XALP.Unload();
        XNDP.Unload();
        XTEL.Unload();
        XSCL.Unload();
        XAPD.Unload();
        XAPR.Unload();
        XLIB.Unload();
        XLKR.Unload();
        XLOC.Unload();
        XLRT.Unload();
        XOWN.Unload();
        XRNK.Unload();
        XCNT.Unload();
        XCVL.Unload();
        XCVR.Unload();
        XCZA.Unload();
        XCZC.Unload();
        XEZN.Unload();
        XFVC.Unload();
        FNAM.Unload();
        FULL.Unload();
        TNAM.Unload();
        XHTW.Unload();
        XLCM.Unload();
        XMBR.Unload();
        XMRK.Unload();
        XPWR.Unload();
        XTRI.Unload();
        XACT.Unload();
        XATR.Unload();
        XWCU.Unload();
        DATA.Unload();
        XTNM.Unload();
        XIS2.Unload();
        XWCN.Unload();
        XPRD.Unload();
        return 1;
    }

    int32_t REFRRecord::WriteRecord(FileWriter &writer)
    {
        WRITE(EDID);
        WRITE(VMAD);
        WRITE(NAME);
        WRITE(XMRK);
        WRITE(XMBO);
        WRITE(XPRM);
        WRITE(XPOD);
        Room.Write(writer);
        WRITE(LNAM);
        WRITE(INAM);
        WRITE(XRGD);
        WRITE(XRDS);
        WRITE(XEMI);
        WRITE(XLIG);
        WRITE(XESP);
        WRITE(XALP);
        WRITE(XNDP);
        WRITE(XTEL);
        WRITE(XSCL);
        WRITE(XAPD);
        WRITE(XAPR);
        WRITE(XLIB);
        WRITE(XLKR);
        WRITE(XLOC);
        WRITE(XLRT);
        WRITE(XOWN);
        WRITE(XRNK);
        WRITE(XCNT);
        WRITE(XCVL);
        WRITE(XCVR);
        WRITE(XCZA);
        WRITE(XCZC);
        WRITE(XEZN);
        WRITE(XFVC);
        WRITE(FNAM);
        WRITE(FULL);
        WRITE(TNAM);
        WRITE(XHTW);
        WRITE(XIS2);
        WRITE(XLCM);
        WRITE(XMBR);
        WRITE(XPWR);
        WRITE(XTRI);
        WRITE(XACT);

        if (openByDefault) {
            writer.record_write_subrecord(REV32(ONAM), NULL, 0);
        }

        WRITE(XATR);
        //Todo convert to OptCounted<UnorderedPackedArray> ..
        WRITE(XWCN);
        WRITE(XWCU);
        //Todo patrol data
        WRITE(XPRD);
        WRITE(DATA);
        return -1;
    }

    bool REFRRecord::operator ==(const REFRRecord &other) const
    {
        return (EDID.equalsi(other.EDID) &&
            VMAD == other.VMAD &&
            NAME == other.NAME &&
            XMBO == other.XMBO &&
            XPRM == other.XPRM &&
            XPOD == other.XPOD &&
            Room == other.Room &&
            LNAM == other.LNAM &&
            INAM == other.INAM &&
            XRGD == other.XRGD &&
            XRDS == other.XRDS &&
            XEMI == other.XEMI &&
            XLIG == other.XLIG &&
            XESP == other.XESP &&
            XALP == other.XALP &&
            XNDP == other.XNDP &&
            XTEL == other.XTEL &&
            XSCL == other.XSCL &&
            XAPD == other.XAPD &&
            XAPR == other.XAPR &&
            XLIB == other.XLIB &&
            XLKR == other.XLKR &&
            XLOC == other.XLOC &&
            XLRT == other.XLRT &&
            XOWN == other.XOWN &&
            XRNK == other.XRNK &&
            XCNT == other.XCNT &&
            XCVL == other.XCVL &&
            XCVR == other.XCVR &&
            XCZA == other.XCZA &&
            XCZC == other.XCZC &&
            XEZN == other.XEZN &&
            XFVC == other.XFVC &&
            FNAM == other.FNAM &&
            FULL.equalsi(other.FULL) &&
            TNAM == other.TNAM &&
            XHTW == other.XHTW &&
            XLCM == other.XLCM &&
            XMBR == other.XMBR &&
            XMRK == other.XMRK &&
            XPWR == other.XPWR &&
            XTRI == other.XTRI &&
            XACT == other.XACT &&
            openByDefault == other.openByDefault &&
            XATR == other.XATR &&
            XWCU == other.XWCU &&
            DATA == other.DATA
            );
    }

    bool REFRRecord::operator !=(const REFRRecord &other) const
    {
        return !(*this == other);
    }

    bool REFRRecord::equals(Record *other)
    {
        return *this == *(REFRRecord *)other;
    }
}