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
#pragma once
// BaseRecord.h
#include <vector>
#include "../Common.h"
#include "../Oblivion/Records/PACKRecord.h"
#include "../Oblivion/Records/DIALRecord.h"
#include "../Skyrim/Records/PACKRecord.h"
#include "../Skyrim/Records/DIALRecord.h"
#include "../Skyrim/Records/DLBRRecord.h"
#include "../Skyrim/SkyrimChunks.h"
#include "../Collection.h"
#include "md5.h"

namespace Skyblivion {

	class SkyblivionScript {

		private:
			std::string scriptPrefix;
			std::string scriptName;
			std::string buildName;
			std::string rootScriptBuildDirectory;
			std::string cachedScriptName;

		public:

			SkyblivionScript(std::string buildName, 
			std::string scriptPrefix, 
			std::string scriptName, 
			std::string rootScriptBuildDirectory):
			scriptPrefix(scriptPrefix),
			scriptName(scriptName),
			buildName(buildName),
			rootScriptBuildDirectory(rootScriptBuildDirectory) {
				//..
			}
			
			std::string getBuildName() const { return this->buildName; }
			std::string getScriptName() { 
				
				if(this->cachedScriptName.empty()) {
					std::string nonprefixedName = this->scriptName;
					std::transform(nonprefixedName.begin(), nonprefixedName.end(), nonprefixedName.begin(), ::tolower);
					std::string scriptName = this->scriptPrefix + nonprefixedName;
					
					if (scriptName.size() > 38) {
						MD5 md5obj;
						char *md5 = md5obj.digestString((char *)nonprefixedName.c_str());
						scriptName = this->scriptPrefix + std::string(md5);
					}

					this->cachedScriptName = scriptName;
				}
				
				return this->cachedScriptName;

			}

			std::string getScriptPath() {
				return rootScriptBuildDirectory + "Transpiled/" + this->buildName + "/" + this->getScriptName() + ".psc";
			}

			std::string getBuiltScriptPath () {
				std::string scriptName = this->scriptName;
				std::transform(scriptName.begin(), scriptName.end(), scriptName.begin(), ::tolower);			
				return rootScriptBuildDirectory + "Artifacts/" + this->buildName + "/" + this->getScriptName() + ".pex";
			}

	};

	class SkyblivionConverter {


	private:
		Sk::PACKRecord::PACKPTDA convertTargetType(Ob::PACKRecord &p);
		Sk::PACKRecord::PACKPLDT convertLocationType(Ob::PACKRecord &p);

		/**
		 * Converts a formid from Oblivion's collection to Skyblivion's ESM
		 * It assumes that Oblivion.esm is expanded into 00 Load Order,
		 * and Skyblivion.esm is expanded into 01 Load Order,
		 */
		FORMID convertFormid(FORMID sourceFormid) {

			//			if (sourceFormid == 0x07) {
			//				sourceFormid = 0x14; //Oblivion old player ref to new player ref
			//			}

						//greeting topic
			if (sourceFormid == 0xC8) {
				sourceFormid = 0x010011C8; //Mapping out of masterspace, above 0x120
			}
			//rumors topic
			if (sourceFormid == 0xD7) {
				sourceFormid = 0x010011D7; //Mapping out of masterspace, above 0x120
			}
			//Races
			else if (sourceFormid == 0x907) {
				sourceFormid = 0x13744; //Imperial
			}
			else if (sourceFormid == 0xD43) {
				sourceFormid = 0x13748; //Redguard
			}
			else if (sourceFormid == 0x191C0) {
				sourceFormid = 0x13747; //Orc
			}
			else if (sourceFormid == 0x191C1) {
				sourceFormid = 0x13742; //Dark Elf
			}
			else if (sourceFormid == 0x19204) {
				sourceFormid = 0x13743; //High Elf
			}
			else if (sourceFormid == 0x223C7) {
				sourceFormid = 0x13745; //Khajiit
			}
			else if (sourceFormid == 0x223C8) {
				sourceFormid = 0x13749; //Wood Elf
			}
			else if (sourceFormid == 0x224FC) {
				sourceFormid = 0x13741; //Breton
			}
			else if (sourceFormid == 0x224FD) {
				sourceFormid = 0x13746; //Nord
			}
			else if (sourceFormid == 0x23FE9) {
				sourceFormid = 0x13740; //Argonian
			}
			else if (sourceFormid == 0x38010) {
				sourceFormid = 0x131F0; //Dremora
			}
			else if (sourceFormid == 0x0B) { 
				sourceFormid = 0x3A070; //Skeleton key
			}
			else if (sourceFormid == 0x191) {
				sourceFormid = 0x0100081E; //Welkynd stone has different formid..
			}
			else if (sourceFormid == 0x193) {
				sourceFormid = 0x63B27; //Azura's star
			}
			else if (sourceFormid == 0x1208E) {
				sourceFormid = 0x13747; //DarkSeducer not present in code, mapped to orc.. FIX IT as its not proper!
			}
			else if (sourceFormid == 0x1208F) {
				sourceFormid = 0x13747; //DarkSeducer not present in code, mapped to orc.. FIX IT as its not proper!
			}
			//Last two formids are SNDS used in DOORs
			else if (sourceFormid != 0x07 && sourceFormid != 0x0A && sourceFormid != 0x13 && sourceFormid != 0x14 && sourceFormid != 0x39 && sourceFormid != 0x38 && sourceFormid != 0x37 && sourceFormid != 0x0F && sourceFormid != 0x00 && sourceFormid != 0x03C813 && sourceFormid != 0x03C810) {
				sourceFormid = (sourceFormid & 0xFFFFFF) + 0x01000000; //Add a 01000000 to everything but gold, lockpick, creature faction,  gameDay, gameHour and null references.
			}

			return sourceFormid;

		}

		const std::string rootBuildPath;
		std::map<std::string, uint32_t> *edidMap;
		std::map<std::string, std::map<uint32_t, uint32_t> *> *targetsMapping;
		Collection &oblivionCollection;
		Collection &skyrimCollection;
		std::vector<Record*, std::allocator<Record*>> scripts;

		Record *findRecordByFormidGeneric(FORMID_OR_UINT32 formid);
		Record *findRecordByFormid(FORMID_OR_UINT32 formid, uint32_t type);

	public:

		SkyblivionConverter(Collection &oblivionCollection, Collection &skyrimCollection, const std::string rootPath);

		const std::string ROOT_BUILD_PATH() const { return rootBuildPath; }
		std::string BUILD_TARGET_STANDALONE() { return "Standalone"; };
		std::string BUILD_TARGET_DIALOGUES() { return "TIF"; }
		std::string BUILD_TARGET_PACKAGES() { return"PF";  }
		std::string BUILD_TARGET_QUESTS() { return "QF"; }

		Sk::QUSTOBJECTIVE * convertObjective(Sk::QUSTRecord *skq, Ob::QUSTRecord::QUSTTarget *obTarget, uint32_t newIndex, std::map<FORMID, int>& formIdToAliasId);
		Script* createVirtualMachineScriptFor(Ob::SCPTRecord* scpt);
		void convertPACKFromOblivion(Ob::PACKRecord& srcRecord, Sk::PACKRecord& dstRecord);
		std::vector<Sk::SKCondition*> convertCTDAFromOblivion(GENCTDA* srcRecord);
        std::vector <Sk::DIALRecord*> * convertDIALFromOblivion();
        std::vector <Sk::QUSTRecord*> * convertQUSTFromOblivion();
		void bindProperties(Script* script, SkyblivionScript &skScript);

		std::map<std::string, std::map<uint32_t, uint32_t>*>* getTargetsMappingTable();

		std::map<std::string, FORMID> *prepareSkyblivionEdidMap();

		void insertToEdidMap(std::string edid, FORMID formid);
		FORMID findRecordFormidByEDID(std::string edid);
		
		TES4File *getOblivionFile() { return (TES4File*)this->oblivionCollection.ModFileByName("Oblivion.esm"); }
		TES5File *getSkyrimFile() { return (TES5File*)this->skyrimCollection.ModFileByName("Skyrim.esm"); }
		TES5File *getSkyblivionFile() { return (TES5File*)this->skyrimCollection.ModFileByName("Skyblivion.esm"); }
		TES5File *getGeckFile() { return (TES5File*)this->skyrimCollection.ModFileByName("GECK.esp"); }

		const std::string getTargetsMappingPath() {
			return this->rootBuildPath + "TargetsMapping";
		}

		const std::map<std::string, uint32_t> &getEdidMap() const { return (*this->edidMap); }  
		const std::vector<Record*, std::allocator<Record*>> &getScripts() const { return this->scripts; }


	};

}