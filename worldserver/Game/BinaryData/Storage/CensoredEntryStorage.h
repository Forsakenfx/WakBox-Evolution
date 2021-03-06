#ifndef BINARYDATA_CENSOREDENTRYSTORAGE_H
#define BINARYDATA_CENSOREDENTRYSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class CensoredEntryStorage : public BinaryDataStorage<T>
{
public:
    CensoredEntryStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            CensoredEntryBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_deepSearch = this->_reader->ReadBool();
            entry.m_language = this->_reader->ReadInt();
            entry.m_censorType = this->_reader->ReadInt();
            entry.m_text = this->_reader->ReadString();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for CensoredEntryStorage";
    }
};

#endif // BINARYDATA_CENSOREDENTRYSTORAGE_H
