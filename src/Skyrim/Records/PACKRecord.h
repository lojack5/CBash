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
#include "../../Common.h"
#include "../../GenericRecord.h"
#include "../../Oblivion/Records/PACKRecord.h"
#include "../SkyrimChunks.h"

namespace Sk
{
	class PACKRecord : public TES5Record //Package
    {



		public: 
			struct PACKPKCU //Template info
			{
				uint32_t dataInputCount;
				uint32_t packageTemplate;
				uint32_t  versionCounter;

				PACKPKCU();
				~PACKPKCU();

				bool operator ==(const PACKPKCU &other) const;
				bool operator !=(const PACKPKCU &other) const;
			};


			struct PACKPTDA //Target
			{
				int32_t targetType;
				FORMID_OR_UINT32 targetId;
				int32_t targetCount;

				PACKPTDA();
				~PACKPTDA();

				bool operator ==(const PACKPTDA &other) const;
				bool operator !=(const PACKPTDA &other) const;
			};

			struct PACKPLDT //Location
			{
				int32_t  locType;
				FORMID_OR_UINT32  locId;
				int32_t  locRadius;

				PACKPLDT();
				~PACKPLDT();

				bool operator ==(const PACKPLDT &other) const;
				bool operator !=(const PACKPLDT &other) const;
			};

			struct PACKPRCB {
				uint32_t numOfChild = 0;
				uint32_t flags = 0;
			};



		struct PACKACTIVITY {
		
				bool writtenBool;
				int writtenInt;
				float writtenFloat;
				PACKPLDT writtenPLDT;
				PACKPTDA writtenPTDA;
			
		};
			
		struct PACKTDAT //Template data..
			{
					std::vector<char *> ANAM;
					std::vector<PACKACTIVITY> cnamData;
					std::vector<uint8_t> unamData;
				
					bool ReadANAM(unsigned char *&buffer, const uint32_t &subSize) {
						char * name = new char[subSize + 1];
						name[subSize] = 0x00;
						memcpy(name, buffer, subSize);
						ANAM.push_back(name);
						buffer += subSize;
						return true;
					}

					bool ReadUNAM(unsigned char *&buffer, const uint32_t &subSize) {
						uint8_t data;
						memcpy(&data, buffer, subSize);
                        buffer += subSize;
						unamData.push_back(data);
						return true;
					}

					bool ReadSelector(unsigned char *&buffer, const uint32_t &subSize) {
						char * lastANAM = ANAM[ANAM.size() - 1];
						PACKACTIVITY p = PACKACTIVITY();

                        if (strcmp(lastANAM, "Bool") == 0) {
                            assert(subSize == 1);
                            memcpy(&p.writtenBool, buffer, subSize);
                        }

                        if (strcmp(lastANAM, "Float") == 0) {
                            assert(subSize == 4);
                            memcpy(&p.writtenFloat, buffer, subSize);
                        }

                        if (strcmp(lastANAM, "Int") == 0) {
                            assert(subSize == 4);
                            memcpy(&p.writtenInt, buffer, subSize);
                        }

                        if (strcmp(lastANAM, "Location") == 0) {
                            memcpy(&p.writtenPLDT, buffer, subSize);
                        }

                        if (strcmp(lastANAM, "SingleRef") == 0) {
                            memcpy(&p.writtenPTDA, buffer, subSize);
                        }

                        if (strcmp(lastANAM, "ObjectList") == 0) {
                            memcpy(&p.writtenFloat, buffer, subSize);
                        }

                        if (strcmp(lastANAM, "TargetSelector") == 0) {
                            memcpy(&p.writtenPTDA, buffer, subSize);
                        }

                        cnamData.push_back(p);
                        buffer += subSize;

						return true;
					}


					void Write(FileWriter &writer) {
						
//						assert(ANAM.size() == cnamData.size() == unamData.size());

						for (uint32_t i = 0; i < ANAM.size(); ++i) {
							std::string stringData = std::string(ANAM[i]);
							size_t sizeString = stringData.size() + 1;

							writer.record_write_subheader(REV32(ANAM),sizeString);
							writer.record_write(stringData.c_str(), sizeString);
							
							if (stringData == "Bool") {
								writer.record_write_subheader(REV32(CNAM), 1);
								writer.record_write(&cnamData[i].writtenBool, 1);
							}

							if (stringData == "Float") {
								writer.record_write_subheader(REV32(CNAM), 4);
								writer.record_write(&cnamData[i].writtenFloat, 4);
							}

							if (stringData == "Int") {
								writer.record_write_subheader(REV32(CNAM), 4);
								writer.record_write(&cnamData[i].writtenInt, 4);
							}

							if (stringData == "Location") {
								int sizeData = sizeof(cnamData[i].writtenPLDT);
								writer.record_write_subheader(REV32(PLDT), sizeData);
								writer.record_write(&cnamData[i].writtenPLDT, sizeData);
							}

							if (stringData == "SingleRef") {
								int sizeData = sizeof(cnamData[i].writtenPTDA);
								writer.record_write_subheader(REV32(PTDA), sizeData);
								writer.record_write(&cnamData[i].writtenPTDA, sizeData);
							}

							if (stringData == "ObjectList") {
								writer.record_write_subheader(REV32(CNAM), 4);
								writer.record_write(&cnamData[i].writtenFloat, 4);
							}

							if (stringData == "TargetSelector") {
								int sizeData = sizeof(cnamData[i].writtenPTDA);
								writer.record_write_subheader(REV32(PTDA), sizeData);
								writer.record_write(&cnamData[i].writtenPTDA, sizeData);
							}

						}

						for (uint32_t i = 0; i < unamData.size(); ++i) {
						
							writer.record_write_subheader(REV32(UNAM), 1);
							writer.record_write(&unamData[i], 1);
						
						}
					}
		
		};
				
        struct PACKPKDT //General
            {
            uint32_t flags;
			uint8_t  packageType;
			uint8_t  interruptOverride;
			uint8_t  preferredSpeed;
			uint8_t  unused1;
			uint32_t  interruptFlags;

            PACKPKDT();
            ~PACKPKDT();

            bool operator ==(const PACKPKDT &other) const;
            bool operator !=(const PACKPKDT &other) const;
            };

        struct PACKPSDT //Schedule
            {
            int8_t   month, day;
            uint8_t   date;
            uint8_t   hour, minute;
			uint8_t unused1[3];
            int32_t  duration;

            PACKPSDT();
            ~PACKPSDT();

            bool operator ==(const PACKPSDT &other) const;
            bool operator !=(const PACKPSDT &other) const;
            };

		struct PACKPTRE {
			char *ANAM = NULL;
			uint32_t CITC;
            UnorderedSparseArray<SKCondition*> CTDA;
			PACKPRCB PRCB;
			char *PNAM = NULL;
			uint32_t FNAM;
			std::vector<uint8_t> PKC2;

            bool ReadANAM(unsigned char *&buffer, const uint32_t &subSize) {
                ANAM = new char[subSize + 1];
                ANAM[subSize] = 0x00;
                memcpy(ANAM, buffer, subSize);
                buffer += subSize;
                return true;
            }

            bool ReadPNAM(unsigned char *&buffer, const uint32_t &subSize) {
                PNAM = new char[subSize + 1];
                PNAM[subSize] = 0x00;
                memcpy(PNAM, buffer, subSize);
                buffer += subSize;
                return true;
            }

            bool ReadPKC2(unsigned char *&buffer, const uint32_t &subSize) {
                uint8_t pkc2;
                memcpy(&pkc2, buffer, subSize);
                buffer += subSize;
                PKC2.push_back(pkc2);
                return true;
            }

			void Write(FileWriter &writer) {
				if (ANAM == NULL)
					return;

				std::string stringData = std::string(ANAM);
				size_t sizeString = stringData.size() + 1;

				writer.record_write_subheader(REV32(ANAM), sizeString);
				writer.record_write(stringData.c_str(), sizeString);

				CITC = std::min((int)CITC, (int)CTDA.value.size());

				writer.record_write_subheader(REV32(CITC), 4);
				writer.record_write(&CITC, 4);

                CTDA.Write(writer);

				if (stringData != "Procedure") {
					int sizeData = sizeof(PRCB);
					writer.record_write_subheader(REV32(PRCB), sizeData);
					writer.record_write(&PRCB, sizeData);
				}
				else {

					if (PNAM != NULL) {
						stringData = std::string(PNAM);
						sizeString = stringData.size() + 1;

						writer.record_write_subheader(REV32(PNAM), sizeString);
						writer.record_write(stringData.c_str(), sizeString);
					}

					writer.record_write_subheader(REV32(FNAM), 4);
					writer.record_write(&FNAM, 4);

					for (int i = 0; i < PKC2.size(); i++) {
						writer.record_write_subheader(REV32(PKC2), 1);
						writer.record_write(&PKC2[i], 1);
					}
				}
			}

            PACKPTRE& operator=(const PACKPTRE& other) {
                ANAM = new char[std::string(other.ANAM).size() + 1];
                std::strcpy(ANAM, other.ANAM);
                CITC = other.CITC;
                CTDA = other.CTDA;
                PRCB = other.PRCB;
                if (other.PNAM != NULL) {
                    PNAM = new char[std::string(other.PNAM).size() + 1];
                    std::strcpy(PNAM, other.PNAM);
                }
                FNAM = other.FNAM;
                PKC2 = other.PKC2;

                return *this;
            }
		};

		struct PACKPDAT {
			uint8_t UNAM;
			char *BNAM = NULL;
			uint32_t PNAM;

            bool ReadBNAM(unsigned char *&buffer, const uint32_t &subSize) {
                BNAM = new char[subSize + 1];
                BNAM[subSize] = 0x00;
                memcpy(BNAM, buffer, subSize);
                buffer += subSize;
                return true;
            }

			void Write(FileWriter &writer) {
				writer.record_write_subheader(REV32(UNAM), 1);
				writer.record_write(&UNAM, 1);

				if(BNAM == NULL)
					writer.record_write_subheader(REV32(BNAM), 0);
				else {
					std::string stringData = std::string(BNAM);
					size_t sizeString = stringData.size() + 1;

					writer.record_write_subheader(REV32(BNAM), sizeString);
					writer.record_write(stringData.c_str(), sizeString);
				}

				writer.record_write_subheader(REV32(PNAM), 4);
				writer.record_write(&PNAM, 4);
			}

            PACKPDAT& operator=(const PACKPDAT& other) {
                BNAM = new char[std::string(other.BNAM).size() + 1];
                std::strcpy(BNAM, other.BNAM);
                UNAM = other.UNAM;
                PNAM = other.PNAM;
                return *this;
            }
		};

		enum interruptFlagsFlags
		{
			fHellosToPlayer = 0x01,
			fRandomConversations = 0x02,
			fObserveCombatBehavior = 0x04,
			fGreetCorpseBehavior = 0x08,
			fReactionToPlayerActions = 0x10,
			fFriendlyFireComments = 0x20,
			fAggroRadiusBehavior = 0x40,
			fAllowIdleChatter = 0x80,
			fWorldInteractions = 0x200
		};

		enum flagsFlags
		{
			fMustComplete = 0x04,
			fMaintainSpeedAtGoal = 0x08,
			fAtPackageStartUnlockDoors = 0x40,
			fAtPackageChangeUnlockDoors = 0x80,
			fOncePerDay = 0x400,
			fPreferredSpeed = 0x2000,
			fAlwaysSneak = 0x20000,
			fAllowSwimming = 0x40000,
			fIgnoreCombat = 0x100000,
			fWeaponsUnequipped = 0x200000,
			fWeaponDrawn = 0x800000,
			fNoCombatAlert = 0x8000000,
			fWearSleepOutfit = 0x20000000
		};
		

		
		enum preferredSpeedTypes
		{
			tWalk = 0,
			tJog = 1,
			tRun = 2,
			tFastWalk = 3
		};

        enum locTypeType
            {
            eLocNearReference       = 0,
            eLocInCell              = 1,
            eLocNearCurrentLocation = 2,
            eLocNearEditorLocation  = 3,
            eLocObjectID            = 4,
            eLocObjectType          = 5
            };

        enum targetTypeType
            {
            eTargetReference  = 0,
            eTargetObjectID   = 1,
            eTargetObjectType = 2
            };

    public:
        StringRecord EDID; //Editor ID
		//TODO ADD VMAD
		
		OrderedSparseArray<SKCondition*> CTDA; //Conditions
		
        ReqSubRecord<PACKPKCU> PKCU; //Template Info
        ReqSubRecord<PACKPKDT> PKDT; //General
        ReqSubRecord<PACKPSDT> PSDT; //Schedule
        ReqSimpleSubRecord<int8_t> XNAM;
        OptSimpleSubRecord<FORMID> CNAM; //Combat style
		PACKTDAT TDAT; //Template data.

		UnorderedSparseArray<PACKPTRE*> PTRE; // Procedure tree
		UnorderedSparseArray<PACKPDAT*> PDAT; // Procedure data
		
        PACKRecord(unsigned char *_recData=NULL);
        PACKRecord(PACKRecord *srcRecord);
        PACKRecord(const PACKRecord &srcRecord);
        ~PACKRecord();

        bool   VisitFormIDs(FormIDOp &op);

		bool isMustComplete();
		bool isMaintainSpeedAtGoal();
		bool isAtPackageStartUnlockDoors();
		bool isAtPackageChangeUnlockDoors();
		bool isOncePerDay();
		bool isPreferredSpeed();
		bool isAlwaysSneak();
		bool isAllowSwimming();
		bool isIgnoreCombat();
		bool isWeaponsUnequipped();
		bool isWeaponDrawn();
		bool isNoCombatAlert();
		bool isWearSleepOutfit();
		void addLocationTemplateSetting(PACKPLDT location, int unamRecordIndex);
		void addBoolTemplateSetting(bool setting, int unamRecordIndex);
		void addIntTemplateSetting(int setting, int unamRecordIndex);
		void addFloatTemplateSetting(float setting, int unamRecordIndex);
		void addTargetTemplateSetting(char * name, PACKPTDA target, int unamRecordIndex);
		void addObjectListTemplateSetting(float setting, int unamRecordIndex);


		//uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        //void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        //bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        //void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);
		char *GetEditorIDKey() { return EDID.value; }

        bool operator ==(const PACKRecord &other) const;
        bool operator !=(const PACKRecord &other) const;
        bool equals(Record *other);

    };
}