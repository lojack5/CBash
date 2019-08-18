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
// Visitors.h
#include "GenericRecord.h"
#include "ModFile.h"

class FormIDMatchCounter : public FormIDOp
    {
    private:
        const uint32_t &FormIDToMatch;

    public:
        FormIDMatchCounter(const uint32_t &_FormIDToMatch);
        ~FormIDMatchCounter();

        bool Accept(uint32_t &curFormID);
        bool AcceptMGEF(uint32_t &curMgefCode);
    };

class RecordUnloader : public RecordOp
    {
    public:
        RecordUnloader();
        ~RecordUnloader();

        bool Accept(Record *&curRecord);
    };

class RecordIDRetriever : public RecordOp
    {
    private:
        RECORDIDARRAY RecordIDs;

    public:
        RecordIDRetriever(RECORDIDARRAY _RecordIDs);
        ~RecordIDRetriever();

        bool Accept(Record *&curRecord);
    };

class FormIDSwapper : public FormIDOp
    {
    private:
        const uint32_t &FormIDToMatch;
        const uint32_t &FormIDToSwap;
        FormIDMasterUpdater checker;

    public:
        FormIDSwapper(const uint32_t &_FormIDToMatch, const uint32_t &_FormIDToSwap, FormIDHandlerClass &_FormIDHandler);
        ~FormIDSwapper();

        bool Accept(uint32_t &curFormID);
        bool AcceptMGEF(uint32_t &curMgefCode);
    };

class RecordIndexer : public RecordOp
    {
    private:
        EditorID_Map &EditorID_ModFile_Record;
		EditorID_Map &EDIDIndex;
		FormID_Map &FormID_ModFile_Record;
        ModFile *curModFile;

    public:
        RecordIndexer(ModFile *_curModFile, EditorID_Map &_EditorID_Map, FormID_Map &_FormID_Map, EditorID_Map &EDIDIndex);
        RecordIndexer(EditorID_Map &_EditorID_Map, FormID_Map &_FormID_Map, EditorID_Map &EDIDIndex);
        ~RecordIndexer();

        bool Accept(Record *&curRecord);

        void SetModFile(ModFile *_curModFile);
    };