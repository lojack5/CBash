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
#include "SCRLRecord.h"

namespace Sk {

	SCRLRecord::SCRLRecord(unsigned char *_recData)
		: TES5Record(_recData)
	{
		//
	}

	SCRLRecord::SCRLRecord(SCRLRecord *srcRecord)
		: TES5Record((TES5Record *)srcRecord)
	{
		if (srcRecord == NULL || !srcRecord->IsChanged())
			return;

		EDID = srcRecord->EDID;
	}

	SCRLRecord::~SCRLRecord()
	{
		//
	}

	uint32_t SCRLRecord::GetType()
	{
		return REV32(SCRL);
	}

	char * SCRLRecord::GetStrType()
	{
		return "SCRL";
	}

	int32_t SCRLRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
	{
		uint32_t subType = 0;
		uint32_t subSize = 0;
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
			case REV32(OBND):
			case REV32(FULL):
			case REV32(MDOB):
			case REV32(KSIZ):
			case REV32(KWDA):
			case REV32(DATA):
			case REV32(ETYP):
			case REV32(DESC):
			case REV32(MODL):
			case REV32(MODT):
			case REV32(MODS):
			case REV32(SPIT):
			case REV32(EFID):
			case REV32(EFIT):
				buffer = end_buffer;
				// Not needed atm
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

	int32_t SCRLRecord::Unload()
	{
		IsLoaded(false);
		IsChanged(false);
		EDID.Unload();
		return 1;
	}

	int32_t SCRLRecord::WriteRecord(FileWriter &writer)
	{
		// Not fully implemented, must not ever be written
		log_error << "SCRL Record is not fully implemented yet!\n";
		std::abort();
		WRITE(EDID);
		return -1;
	}

	bool SCRLRecord::operator ==(const SCRLRecord &other) const
	{
		return (EDID.equalsi(other.EDID)
			);
	}

	bool SCRLRecord::operator !=(const SCRLRecord &other) const
	{
		return !(*this == other);
	}

	bool SCRLRecord::equals(Record *other)
	{
		try
		{
			return *this == *dynamic_cast<const SCRLRecord *>(other);
		}
		catch (...)
		{
			return false;
		}
	}

} // namespace Sk
