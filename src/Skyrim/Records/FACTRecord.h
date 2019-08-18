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
#include "../SkyrimChunks.h"

namespace Sk
{
struct sortRNAM;

class FACTRecord : public TES5Record //Faction
    {
    private:

        struct FACTRNAM //Rank
            {
            ReqSimpleSubRecord<int32_t> RNAM; //Rank#
            StringRecord MNAM, FNAM; //Male, Female

            void Write(FileWriter &writer);

            bool operator ==(const FACTRNAM &other) const;
            bool operator !=(const FACTRNAM &other) const;
            };
			
        struct TES5CRVA //Rank
		{
			uint8_t arrests;
			uint8_t attacksOnSight;
			uint16_t murder;
			uint16_t assault;
			uint16_t trespass;
			uint16_t pickpocket;
			uint16_t unused;
			float stealMult;
			uint16_t escape;
			uint16_t werewolf;
			
            bool operator ==(const TES5CRVA &other) {
				return (
					arrests == other.arrests &&
					attacksOnSight == other.attacksOnSight &&
					murder == other.murder &&
					assault == other.assault &&
					trespass == other.trespass &&
					pickpocket == other.pickpocket &&
					unused == other.unused &&
					stealMult == other.stealMult &&
					escape == other.escape &&
					werewolf == other.werewolf
				);
			}
			
            bool operator !=(const TES5CRVA &other) {
				return !(*this == other);
			}
            
		};			
		
        struct TES5VENV //Rank
		{
			uint16_t startHour;
			uint16_t endHour;
			uint32_t radius;
			uint8_t buysStolen;
			uint8_t negativeVendorList;
			uint16_t unused;
			
            bool operator ==(const TES5VENV &other) {
				return (
					startHour == other.startHour &&
					endHour == other.endHour &&
					radius == other.radius &&
					buysStolen == other.buysStolen &&
					negativeVendorList == other.negativeVendorList
				);
			}
			
            bool operator !=(const TES5VENV &other) {
				return !(*this == other);
			}
            
		};		

        struct TES5PLVD //Rank
		{
			uint32_t specificationType;
			FORMID formid;
			uint32_t unused;
			
            bool operator ==(const TES5PLVD &other) {
				return (
					specificationType == other.specificationType &&
					formid == other.formid
				);
			}
			
            bool operator !=(const TES5PLVD &other) {
				return !(*this == other);
			}
            
		};					

        enum flagsFlags
            {
            fIsHiddenFromPC  = 0x0001,
            fIsEvil          = 0x0002,
            fIsSpecialCombat = 0x0004,
            fIsTrackCrime    = 0x0100,
            fIsAllowSell     = 0x0200
            };

        friend sortRNAM;

    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        OrderedSparseArray<FNVXNAM *> XNAM; //Relations, not sure if record order matters
        ReqSubRecord<uint32_t> DATA; //Data
        OptSimpleSubRecord<FORMID> JAIL;
        OptSimpleSubRecord<FORMID> WAIT;
        OptSimpleSubRecord<FORMID> STOL;
        OptSimpleSubRecord<FORMID> PLCN;
        OptSimpleSubRecord<FORMID> CRGR;
        OptSimpleSubRecord<FORMID> JOUT;
        OptSubRecord<TES5CRVA> CRVA;
				
        OrderedSparseArray<FACTRNAM *, sortRNAM> RNAM; //Ranks
        OptSimpleSubRecord<FORMID> VEND;
        OptSimpleSubRecord<FORMID> VENC;
        OptSubRecord<TES5VENV> VENV;		
        OptSubRecord<TES5PLVD> PLVD;		
        OptCounted<UnorderedSparseArray<SKCTDA*>, uint32_t, REV32(CITC)> CTDA;
		
        FACTRecord(unsigned char *_recData=NULL);
        FACTRecord(FACTRecord *srcRecord);
        ~FACTRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsHiddenFromPC();
        void   IsHiddenFromPC(bool value);
        bool   IsEvil();
        void   IsEvil(bool value);
        bool   IsSpecialCombat();
        void   IsSpecialCombat(bool value);
        bool   IsTrackCrime();
        void   IsTrackCrime(bool value);
        bool   IsAllowSell();
        void   IsAllowSell(bool value);
        bool   IsFlagMask(uint16_t Mask, bool Exact=false);
        void   SetFlagMask(uint16_t Mask);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);
		char *GetEditorIDKey() { return EDID.value; }

        bool operator ==(const FACTRecord &other) const;
        bool operator !=(const FACTRecord &other) const;
        bool equals(Record *other);
    };

struct sortRNAM
    {

		bool operator()(const FACTRecord::FACTRNAM *lhs, const FACTRecord::FACTRNAM *rhs) const
		{
			return lhs->RNAM.value < rhs->RNAM.value;
		}

    };
}