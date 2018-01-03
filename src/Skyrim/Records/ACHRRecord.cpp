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
#include "ACHRRecord.h"

namespace Sk
{
	ACHRRecord::ACHRRecord(unsigned char *_recData) :
		TES5Record(_recData)
	{
		//
	}

	ACHRRecord::ACHRRecord(ACHRRecord *srcRecord) :
		TES5Record()
	{
		if (srcRecord == NULL)
			return;

		EDID = srcRecord->EDID;
		VMAD = srcRecord->VMAD;
		NAME = srcRecord->NAME;
		XEZN = srcRecord->XEZN;
		XPRD = srcRecord->XPRD;
		XPPA = srcRecord->XPPA;
		INAM = srcRecord->INAM;
		PDTO = srcRecord->PDTO;
		XRGD = srcRecord->XRGD;
		XRGB = srcRecord->XRGB;
		XLCM = srcRecord->XLCM;
		XAPD = srcRecord->XAPD;
		XAPR = srcRecord->XAPR;
		XLRT = srcRecord->XLRT;
		XHOR = srcRecord->XHOR;
		XESP = srcRecord->XESP;
		XOWN = srcRecord->XOWN;
		XLCN = srcRecord->XLCN;
		XLKR = srcRecord->XLKR;
		XIS2 = srcRecord->XIS2;
		XLRL = srcRecord->XLRL;
		XSCL = srcRecord->XSCL;
		DATA = srcRecord->DATA;

		if (!srcRecord->IsChanged())
			return;

		return;
	}

	ACHRRecord::~ACHRRecord()
	{
		//
	}

	uint32_t ACHRRecord::GetType()
	{
		return REV32(ACHR);
	}

	char * ACHRRecord::GetStrType()
	{
		return "ACHR";
	}


	bool ACHRRecord::VisitFormIDs(FormIDOp &op)
	{
		if (!IsLoaded())
			return false;
		if (VMAD.IsLoaded()) {
			//TODO - implement VisitFormIDs for struct VMADRecord
		}
		op.Accept(NAME.value);
		if (XEZN.IsLoaded()) {
			op.Accept(XEZN.value);
		}
		if (INAM.IsLoaded()) {
			op.Accept(INAM.value);
		}
		if (PDTO.IsLoaded()) {
			//TODO - implement VisitFormIDs for struct PDTO
		}
		if (XAPR.IsLoaded()) {
			//TODO - implement VisitFormIDs for struct GENXAPR
		}
		if (XLRT.IsLoaded()) {
			for (uint32_t i = 0; i < XLRT.value.size(); ++i) {

				op.Accept(XLRT.value[i]);

			};
		}
		if (XHOR.IsLoaded()) {
			op.Accept(XHOR.value);
		}
		if (XESP.IsLoaded()) {
			//TODO - implement VisitFormIDs for struct GENXESP
		}
		if (XOWN.IsLoaded()) {
			op.Accept(XOWN.value);
		}
		if (XLCN.IsLoaded()) {
			op.Accept(XLCN.value);
		}
		if (XLKR.IsLoaded()) {
			//TODO - implement VisitFormIDs for struct XLKR
		}
		if (XLRL.IsLoaded()) {
			op.Accept(XLRL.value);
		}
		if (DATA.IsLoaded()) {
			//TODO - implement VisitFormIDs for struct GENPOSDATA
		}

		return op.Stop();
	}


	int32_t ACHRRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
	{
		uint32_t subType = 0;
		uint32_t subSize = 0;
		while (buffer < end_buffer) {
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
                VMAD.value->Read(buffer, subSize, REV32(ACHR), CompressedOnDisk);
				break;
			case REV32(NAME):
				NAME.Read(buffer, subSize);
				break;
			case REV32(XEZN):
				XEZN.Read(buffer, subSize);
				break;
			case REV32(XPRD):
				XPRD.Read(buffer, subSize);
				break;
			case REV32(XPPA):
				XPPA.Read(buffer, subSize, CompressedOnDisk);
				break;
			case REV32(INAM):
				INAM.Read(buffer, subSize);
				break;
			case REV32(PDTO):
				PDTO.Read(buffer, subSize);
				break;
			case REV32(XRGD):
				XRGD.Read(buffer, subSize, CompressedOnDisk);
				break;
			case REV32(XRGB):
				XRGB.Read(buffer, subSize, CompressedOnDisk);
				break;
			case REV32(XLCM):
				XLCM.Read(buffer, subSize);
				break;
			case REV32(XAPD):
				XAPD.Read(buffer, subSize);
				break;
			case REV32(XAPR):
				XAPR.Read(buffer, subSize);
				break;
			case REV32(XLRT):
				XLRT.Read(buffer, subSize);
				break;
			case REV32(XHOR):
				XHOR.Read(buffer, subSize);
				break;
			case REV32(XESP):
				XESP.Read(buffer, subSize);
				break;
			case REV32(XOWN):
				XOWN.Read(buffer, subSize);
				break;
			case REV32(XLCN):
				XLCN.Read(buffer, subSize);
				break;
			case REV32(XLKR):
				XLKR.Read(buffer, subSize);
				break;
			case REV32(XIS2):
				XIS2.Read(buffer, subSize, CompressedOnDisk);
				break;
			case REV32(XLRL):
				XLRL.Read(buffer, subSize);
				break;
			case REV32(XSCL):
				XSCL.Read(buffer, subSize);
				break;
			case REV32(DATA):
				DATA.Read(buffer, subSize);
				break;

			default:
				//printer("FileName = %s\n", FileName);
				printer("  ACHR: %08X - Unknown subType = %04x [%c%c%c%c]\n", formID, subType, (subType >> 0) & 0xFF, (subType >> 8) & 0xFF, (subType >> 16) & 0xFF, (subType >> 24) & 0xFF);
				CBASH_CHUNK_DEBUG
					printer("  Size = %i\n", subSize);
				printer("  CurPos = %08x\n\n", buffer - 6);
				buffer = end_buffer;
				break;
			}
		};
		return 0;
	}

	int32_t ACHRRecord::Unload()
	{
		IsChanged(false);
		IsLoaded(false);
		EDID.Unload();
		VMAD.Unload();
		NAME.Unload();
		XEZN.Unload();
		XPRD.Unload();
		XPPA.Unload();
		INAM.Unload();
		PDTO.Unload();
		XRGD.Unload();
		XRGB.Unload();
		XLCM.Unload();
		XAPD.Unload();
		XAPR.Unload();
		XLRT.Unload();
		XHOR.Unload();
		XESP.Unload();
		XOWN.Unload();
		XLCN.Unload();
		XLKR.Unload();
		XIS2.Unload();
		XLRL.Unload();
		XSCL.Unload();
		DATA.Unload();

		return 1;
	}

	int32_t ACHRRecord::WriteRecord(FileWriter &writer)
	{
		WRITE(EDID);
		WRITE(VMAD);
		WRITE(NAME);
		WRITE(XEZN);
		WRITE(XPRD);
		WRITE(XPPA);
		WRITE(INAM);
		WRITE(PDTO);
		WRITE(XRGD);
		WRITE(XRGB);
		WRITE(XLCM);
		WRITE(XAPD);
		WRITE(XAPR);
		WRITE(XLRT);
		WRITE(XHOR);
		WRITE(XESP);
		WRITE(XOWN);
		WRITE(XLCN);
		WRITE(XLKR);
		WRITE(XIS2);
		WRITE(XLRL);
		WRITE(XSCL);
		WRITE(DATA);
		return -1;
	}

	bool ACHRRecord::operator ==(const ACHRRecord &other) const
	{
		return (EDID.equalsi(other.EDID) &&
			VMAD == other.VMAD &&
			NAME == other.NAME &&
			XEZN == other.XEZN &&
			XPRD == other.XPRD &&
			XPPA == other.XPPA &&
			INAM == other.INAM &&
			PDTO == other.PDTO &&
			XRGD == other.XRGD &&
			XRGB == other.XRGB &&
			XLCM == other.XLCM &&
			XAPD == other.XAPD &&
			XAPR == other.XAPR &&
			XLRT == other.XLRT &&
			XHOR == other.XHOR &&
			XESP == other.XESP &&
			XOWN == other.XOWN &&
			XLCN == other.XLCN &&
			XLKR == other.XLKR &&
			XIS2 == other.XIS2 &&
			XLRL == other.XLRL &&
			XSCL == other.XSCL &&
			DATA == other.DATA);
	}

	bool ACHRRecord::operator !=(const ACHRRecord &other) const
	{
		return !(*this == other);
	}

	bool ACHRRecord::equals(Record *other)
	{
		return *this == *(ACHRRecord *)other;
	}
}