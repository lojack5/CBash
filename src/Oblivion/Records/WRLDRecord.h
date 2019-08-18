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
#include "../../Allocator.h"
#include "CELLRecord.h"
//#include "ROADRecord.h"
#include <vector>

namespace Ob
{
class WRLDRecord : public Record
    {
    private:
        enum flagsFlags
            {
            fSmallWorld         = 0x00000001,
            fNoFastTravel       = 0x00000002,
            fOblivionWorldspace = 0x00000004,
            fNoLODWater         = 0x00000010
            };

        enum eSNAMType
            {
            eDefault = 0,
            ePublic  = 1,
            eDungeon = 2
            };

    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        OptSimpleSubRecord<FORMID> WNAM; //Parent Worldspace
        OptSimpleSubRecord<FORMID> CNAM; //Climate
        OptSimpleSubRecord<FORMID/*, 0x18*/> NAM2; //Water
        SemiOptSimpleFloatSubRecord<flt_0> NAM4; //LOD Water Height
        StringRecord ICON; //Large Icon Filename
        SemiOptSubRecord<GENMNAM> MNAM; //Map Data
        ReqSimpleSubRecord<uint8_t, fSmallWorld> DATA; //Flags
        ReqSubRecord<GENNAM0> NAM0; //Min Object Bounds
        ReqSubRecord<GENNAM9> NAM9; //Max Object Bounds
        OptSimpleSubRecord<uint32_t> SNAM; //Sound Type
        RawRecord OFST; //Unknown

        Record *ROAD;
        Record *CELL;
        std::vector<Record *> CELLS;

        WRLDRecord(unsigned char *_recData=NULL);
        WRLDRecord(WRLDRecord *srcRecord);
        ~WRLDRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsSmallWorld();
        void   IsSmallWorld(bool value);
        bool   IsNoFastTravel();
        void   IsNoFastTravel(bool value);
        bool   IsFastTravel();
        void   IsFastTravel(bool value);
        bool   IsOblivionWorldspace();
        void   IsOblivionWorldspace(bool value);
        bool   IsNoLODWater();
        void   IsNoLODWater(bool value);
        bool   IsLODWater();
        void   IsLODWater(bool value);
        bool   IsFlagMask(uint8_t Mask, bool Exact=false);
        void   SetFlagMask(uint8_t Mask);

        bool   IsDefaultMusic();
        void   IsDefaultMusic(bool value);
        bool   IsPublicMusic();
        void   IsPublicMusic(bool value);
        bool   IsDungeonMusic();
        void   IsDungeonMusic(bool value);
        bool   IsMusicType(uint32_t Type);
        void   SetMusicType(uint32_t Type);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const WRLDRecord &other) const;
        bool operator !=(const WRLDRecord &other) const;
        bool equals(Record *other);
        bool deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records);
    };
}