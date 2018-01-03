#pragma once
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
#include "../../ModFile.h"
#include "WEAPRecord.h"

namespace Sk
{
	WEAPRecord::WEAPRecord(unsigned char *_recData) :
		TES5Record(_recData)
	{
		//
	}

	WEAPRecord::WEAPRecord(WEAPRecord *srcRecord) :
		TES5Record()
	{
		if (srcRecord == NULL)
			return;

		flags = srcRecord->flags;
		formID = srcRecord->formID;
		flagsUnk = srcRecord->flagsUnk;
		formVersion = srcRecord->formVersion;
		versionControl2[0] = srcRecord->versionControl2[0];
		versionControl2[1] = srcRecord->versionControl2[1];

		recData = srcRecord->recData;
		if (!srcRecord->IsChanged())
			return;
		EDID = srcRecord->EDID;
		VMAD = srcRecord->VMAD;
		OBND = srcRecord->OBND;
		FULL = srcRecord->FULL;
		MODL = srcRecord->MODL;
		EITM = srcRecord->EITM;
		EAMT = srcRecord->EAMT;
		DEST = srcRecord->DEST;
		ETYP = srcRecord->ETYP;
		BIDS = srcRecord->BIDS;
		BAMT = srcRecord->BAMT;
		YNAM = srcRecord->YNAM;
		ZNAM = srcRecord->ZNAM;
		KWDA = srcRecord->KWDA;
		DESC = srcRecord->DESC;
		INAM = srcRecord->INAM;
		WNAM = srcRecord->WNAM;
		SNAM = srcRecord->SNAM;
		XNAM = srcRecord->XNAM;
		NAM7 = srcRecord->NAM7;
		TNAM = srcRecord->TNAM;
		UNAM = srcRecord->UNAM;
		NAM9 = srcRecord->NAM9;
		NAM8 = srcRecord->NAM8;
		DATA = srcRecord->DATA;
		DNAM = srcRecord->DNAM;
		CRDT = srcRecord->CRDT;
		VNAM = srcRecord->VNAM;
		CNAM = srcRecord->CNAM;


		return;
	}

	WEAPRecord::~WEAPRecord()
	{
		//
	}

	uint32_t WEAPRecord::GetType()
	{
		return REV32(WEAP);
	}

	char * WEAPRecord::GetStrType()
	{
		return "WEAP";
	}


	bool WEAPRecord::VisitFormIDs(FormIDOp &op)
	{
		if (!IsLoaded())
			return false;
		//TODO - implement VisitFormIDs for struct GENOBND

		if (EITM.IsLoaded()) {
			op.Accept(EITM.value);
		}
		if (DEST.IsLoaded()) {
			//TODO - implement VisitFormIDs for struct GENDESTRUCT
		}
		if (ETYP.IsLoaded()) {
			op.Accept(ETYP.value);
		}
		if (BIDS.IsLoaded()) {
			op.Accept(BIDS.value);
		}
		if (BAMT.IsLoaded()) {
			op.Accept(BAMT.value);
		}
		if (YNAM.IsLoaded()) {
			op.Accept(YNAM.value);
		}
		if (ZNAM.IsLoaded()) {
			op.Accept(ZNAM.value);
		}
		if (KWDA.IsLoaded()) {
			for (uint32_t i = 0; i < KWDA.value.size(); ++i) {

				op.Accept(KWDA.value[i]);

			};
		}
		if (INAM.IsLoaded()) {
			op.Accept(INAM.value);
		}
		if (WNAM.IsLoaded()) {
			op.Accept(WNAM.value);
		}
		if (SNAM.IsLoaded()) {
			op.Accept(SNAM.value);
		}
		if (XNAM.IsLoaded()) {
			op.Accept(XNAM.value);
		}
		if (NAM7.IsLoaded()) {
			op.Accept(NAM7.value);
		}
		if (TNAM.IsLoaded()) {
			op.Accept(TNAM.value);
		}
		if (UNAM.IsLoaded()) {
			op.Accept(UNAM.value);
		}
		if (NAM9.IsLoaded()) {
			op.Accept(NAM9.value);
		}
		if (NAM8.IsLoaded()) {
			op.Accept(NAM8.value);
		}
		if (DATA.IsLoaded()) {
			//TODO - implement VisitFormIDs for struct WEAPDATA
		}
		if (DNAM.IsLoaded()) {
			//TODO - implement VisitFormIDs for struct WEAPDNAM
		}
		if (CRDT.IsLoaded()) {
			//TODO - implement VisitFormIDs for struct WEAPCRDT
		}
		if (CNAM.IsLoaded()) {
			op.Accept(CNAM.value);
		}

		return op.Stop();
	}


	int32_t WEAPRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
	{
		uint32_t subType = 0;
		uint32_t subSize = 0;
		StringLookups *LookupStrings = GetParentMod()->TES4.LookupStrings;
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
				VMAD.Read(buffer, subSize, GetType(), CompressedOnDisk);
				break;
			case REV32(OBND):
				OBND.Read(buffer, subSize);
				break;
			case REV32(FULL):
				FULL.Read(buffer, subSize, CompressedOnDisk, LookupStrings);
				break;
			case REV32(MODL):
				MODL.MODL.Read(buffer, subSize, CompressedOnDisk);
				break;
			case REV32(MODT):
				MODL.MODT.Read(buffer, subSize, CompressedOnDisk);
				break;
			case REV32(EITM):
				EITM.Read(buffer, subSize);
				break;
			case REV32(EAMT):
				EAMT.Read(buffer, subSize);
				break;
			case REV32(DEST):
				DEST.Read(buffer, subSize);
				break;
			case REV32(ETYP):
				ETYP.Read(buffer, subSize);
				break;
			case REV32(BIDS):
				BIDS.Read(buffer, subSize);
				break;
			case REV32(BAMT):
				BAMT.Read(buffer, subSize);
				break;
			case REV32(YNAM):
				YNAM.Read(buffer, subSize);
				break;
			case REV32(ZNAM):
				ZNAM.Read(buffer, subSize);
				break;
			case REV32(KSIZ):
				// Ignore on read
				buffer += subSize;
				break;
			case REV32(KWDA):
				KWDA.Read(buffer, subSize);
				break;
			case REV32(DESC):
				DESC.Read(buffer, subSize, CompressedOnDisk, LookupStrings);
				break;
			case REV32(INAM):
				INAM.Read(buffer, subSize);
				break;
			case REV32(WNAM):
				WNAM.Read(buffer, subSize);
				break;
			case REV32(SNAM):
				SNAM.Read(buffer, subSize);
				break;
			case REV32(XNAM):
				XNAM.Read(buffer, subSize);
				break;
			case REV32(NAM7):
				NAM7.Read(buffer, subSize);
				break;
			case REV32(TNAM):
				TNAM.Read(buffer, subSize);
				break;
			case REV32(UNAM):
				UNAM.Read(buffer, subSize);
				break;
			case REV32(NAM9):
				NAM9.Read(buffer, subSize);
				break;
			case REV32(NAM8):
				NAM8.Read(buffer, subSize);
				break;
			case REV32(DATA):
				DATA.Read(buffer, subSize);
				break;
			case REV32(DNAM):
				DNAM.Read(buffer, subSize);
				break;
			case REV32(CRDT):
				CRDT.Read(buffer, subSize);
				break;
			case REV32(VNAM):
				VNAM.Read(buffer, subSize);
				break;
			case REV32(CNAM):
				CNAM.Read(buffer, subSize);
				break;

			default:
				//printer("FileName = %s\n", FileName);
				printer("  WEAP: %08X - Unknown subType = %04x [%c%c%c%c]\n", formID, subType, (subType >> 0) & 0xFF, (subType >> 8) & 0xFF, (subType >> 16) & 0xFF, (subType >> 24) & 0xFF);
				CBASH_CHUNK_DEBUG
					printer("  Size = %i\n", subSize);
				printer("  CurPos = %08x\n\n", buffer - 6);
				buffer = end_buffer;
				break;
			}
		};
		return 0;
	}

	int32_t WEAPRecord::Unload()
	{
		IsChanged(false);
		IsLoaded(false);
		EDID.Unload();
		VMAD.Unload();
		OBND.Unload();
		FULL.Unload();
		EITM.Unload();
		EAMT.Unload();
		DEST.Unload();
		ETYP.Unload();
		BIDS.Unload();
		BAMT.Unload();
		YNAM.Unload();
		ZNAM.Unload();
		KWDA.Unload();
		DESC.Unload();
		INAM.Unload();
		WNAM.Unload();
		SNAM.Unload();
		XNAM.Unload();
		NAM7.Unload();
		TNAM.Unload();
		UNAM.Unload();
		NAM9.Unload();
		NAM8.Unload();
		DATA.Unload();
		DNAM.Unload();
		CRDT.Unload();
		VNAM.Unload();
		CNAM.Unload();

		return 1;
	}

	int32_t WEAPRecord::WriteRecord(FileWriter &writer)
	{
		WRITE(EDID);
		WRITE(VMAD);
		WRITE(OBND);
		WRITE(FULL);
		MODL.Write(writer);
		WRITE(EITM);
		WRITE(EAMT);
		WRITE(DEST);
		WRITE(ETYP);
		WRITE(BIDS);
		WRITE(BAMT);
		WRITE(YNAM);
		WRITE(ZNAM);
		WRITE(KWDA);
		WRITE(DESC);
		WRITE(INAM);
		WRITE(WNAM);
		WRITE(SNAM);
		WRITE(XNAM);
		WRITE(NAM7);
		WRITE(TNAM);
		WRITE(UNAM);
		WRITE(NAM9);
		WRITE(NAM8);
		WRITE(DATA);
		WRITE(DNAM);
		WRITE(CRDT);
		WRITE(VNAM);
		WRITE(CNAM);
		return -1;
	}

	bool WEAPRecord::operator ==(const WEAPRecord &other) const
	{
		return (EDID.equalsi(other.EDID) &&
			VMAD == other.VMAD &&
			OBND == other.OBND &&
			FULL.equalsi(other.FULL) &&
			MODL == other.MODL &&
			EITM == other.EITM &&
			EAMT == other.EAMT &&
			DEST == other.DEST &&
			ETYP == other.ETYP &&
			BIDS == other.BIDS &&
			BAMT == other.BAMT &&
			YNAM == other.YNAM &&
			ZNAM == other.ZNAM &&
			KWDA == other.KWDA &&
			DESC.equalsi(other.DESC) &&
			INAM == other.INAM &&
			WNAM == other.WNAM &&
			SNAM == other.SNAM &&
			XNAM == other.XNAM &&
			NAM7 == other.NAM7 &&
			TNAM == other.TNAM &&
			UNAM == other.UNAM &&
			NAM9 == other.NAM9 &&
			NAM8 == other.NAM8 &&
			DATA == other.DATA &&
			DNAM == other.DNAM &&
			CRDT == other.CRDT &&
			VNAM == other.VNAM &&
			CNAM == other.CNAM);
	}

	bool WEAPRecord::operator !=(const WEAPRecord &other) const
	{
		return !(*this == other);
	}

	bool WEAPRecord::equals(Record *other)
	{
		return *this == *(WEAPRecord *)other;
	}
}