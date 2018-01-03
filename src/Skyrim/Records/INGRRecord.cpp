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
#include "INGRRecord.h"

namespace Sk
{
	INGRRecord::INGRRecord(unsigned char *_recData) :
		TES5Record(_recData)
	{
		//
	}
	
	INGRRecord::INGRRecord(INGRRecord *srcRecord) :
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
		if(!srcRecord->IsChanged())
			return;
		EDID = srcRecord->EDID;
		VMAD = srcRecord->VMAD;
		OBND = srcRecord->OBND;
		FULL = srcRecord->FULL;
		MODL = srcRecord->MODL;
		KWDA = srcRecord->KWDA;
		ICON = srcRecord->ICON;
		YNAM = srcRecord->YNAM;
		ZNAM = srcRecord->ZNAM;
		DATA = srcRecord->DATA;
		ENIT = srcRecord->ENIT;
		effects = srcRecord->effects;


		return;
	}

	INGRRecord::~INGRRecord()
	{
		//
	}

	uint32_t INGRRecord::GetType()
	{
		return REV32(INGR);
	}

	char * INGRRecord::GetStrType()
	{
		return "INGR";
	}


	bool INGRRecord::VisitFormIDs(FormIDOp &op)
	{
		if (!IsLoaded())
			return false;
		if (VMAD.IsLoaded()) {
			//TODO - implement VisitFormIDs for struct VMADRecord
		}
		//TODO - implement VisitFormIDs for struct GENOBND

		if (KWDA.IsLoaded()) {
			for (uint32_t i = 0; i < KWDA.value.size(); ++i) {

				op.Accept(KWDA.value[i]);

			};
		}
		if (YNAM.IsLoaded()) {
			op.Accept(YNAM.value);
		}
		if (ZNAM.IsLoaded()) {
			op.Accept(ZNAM.value);
		}
		//TODO - implement VisitFormIDs for struct ItemData

		//TODO - implement VisitFormIDs for struct EnchantedItem


		return op.Stop();
	}


	int32_t INGRRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
	{
		uint32_t subType = 0;
		uint32_t subSize = 0;
		StringLookups *LookupStrings = GetParentMod()->TES4.LookupStrings;
		SpellEffect *currentEffect = NULL;
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
                VMAD.value->Read(buffer, subSize, REV32(INGR), CompressedOnDisk);
				break;
			case REV32(OBND):
				OBND.Read(buffer, subSize);
				break;
			case REV32(FULL):
				FULL.Read(buffer, subSize, CompressedOnDisk, LookupStrings);
				break;
			case REV32(KSIZ):
				// Number of KWDAs
				buffer += subSize;
				break;
			case REV32(KWDA):
				KWDA.Read(buffer, subSize);
				break;
			case REV32(MODL):
				MODL.MODL.Read(buffer, subSize, CompressedOnDisk);
				break;
			case REV32(MODT):
				MODL.MODT.Read(buffer, subSize, CompressedOnDisk);
				break;
			case REV32(MODS):
				MODL.Textures.Read(buffer, subSize);
				break;				
			case REV32(ICON):
				ICON.Read(buffer, subSize, CompressedOnDisk);
				break;
			case REV32(YNAM):
				YNAM.Read(buffer, subSize);
				break;
			case REV32(ZNAM):
				ZNAM.Read(buffer, subSize);
				break;
			case REV32(DATA):
				DATA.Read(buffer, subSize);
				break;
			case REV32(ENIT):
				ENIT.Read(buffer, subSize);
				break;
			case REV32(EFID):
				currentEffect = new SpellEffect();
				effects.value.push_back(currentEffect);
				currentEffect->EFID.Read(buffer, subSize);
				break;
				
			case REV32(EFIT):
				if(currentEffect != NULL) {
					currentEffect->EFIT.Read(buffer, subSize);
				} else {
					printer("  INGR: %08X - EFIT found without an effect initialized\n", formID);
					buffer += subSize;
				} 
				
				break;
										
			case REV32(CTDA):
				if(currentEffect != NULL) {
					currentEffect->CTDA.Read(buffer, subSize);
				} else {
					printer("  INGR: %08X - CTDA found without an effect initialized\n", formID);
					buffer += subSize;
				} 
			
				break;
											
			
		default:
				//printer("FileName = %s\n", FileName);
				printer("  INGR: %08X - Unknown subType = %04x [%c%c%c%c]\n", formID, subType, (subType >> 0) & 0xFF, (subType >> 8) & 0xFF, (subType >> 16) & 0xFF, (subType >> 24) & 0xFF);
				CBASH_CHUNK_DEBUG
					printer("  Size = %i\n", subSize);
				printer("  CurPos = %08x\n\n", buffer - 6);
				buffer = end_buffer;
				break;
			}
		};
		return 0;
	}

	int32_t INGRRecord::Unload()
	{
		IsChanged(false);
		IsLoaded(false);
		EDID.Unload();
		VMAD.Unload();
		OBND.Unload();
		FULL.Unload();
		//MODL.Unload();
		KWDA.Unload();
		ICON.Unload();
		YNAM.Unload();
		ZNAM.Unload();
		DATA.Unload();
		ENIT.Unload();
		//effects.Unload();

		return 1;
	}

	int32_t INGRRecord::WriteRecord(FileWriter &writer)
	{	
		WRITE(EDID);
		WRITE(VMAD);
		WRITE(OBND);
		WRITE(FULL);
		MODL.Write(writer);
		WRITE(KWDA);
		WRITE(ICON);
		WRITE(YNAM);
		WRITE(ZNAM);
		WRITE(DATA);
		WRITE(ENIT);
		effects.Write(writer);
		return -1;
	}

	bool INGRRecord::operator ==(const INGRRecord &other) const
	{
		return (EDID.equalsi(other.EDID) &&
			VMAD == other.VMAD &&
			OBND == other.OBND &&
			FULL.equalsi(other.FULL) &&
			KWDA == other.KWDA &&
			MODL == other.MODL &&
			ICON.equalsi(other.ICON) &&
			YNAM == other.YNAM &&
			ZNAM == other.ZNAM &&
			DATA == other.DATA &&
			ENIT == other.ENIT &&
			effects == other.effects);
	}

	bool INGRRecord::operator !=(const INGRRecord &other) const
	{
		return !(*this == other);
	}

	bool INGRRecord::equals(Record *other)
	{
		return *this == *(INGRRecord *)other;
	}
}