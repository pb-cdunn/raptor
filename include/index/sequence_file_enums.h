/*
 * sequence_file_enums.h
 *
 *  Created on: Dec 23, 2018
 *      Author: Ivan Sovic
 */

#ifndef SRC_PARAMS_SEQUENCE_FILE_ENUMS_H_
#define SRC_PARAMS_SEQUENCE_FILE_ENUMS_H_

#include <algorithm>
#include <cstdlib>

namespace mindex {

enum class BatchLoadType { MB, Coverage };
enum class SequenceFormat { Auto, Fasta, Fastq, SAM, BAM, GFA, GFA1, GFA2, RaptorDB, FOFN, Unknown };

inline SequenceFormat SequenceFormatFromString(const std::string& format_str) {
    SequenceFormat ret;
    if (format_str == "auto") {
        ret = SequenceFormat::Auto;
    } else if (format_str == "fasta" || format_str == "fa") {
        ret = SequenceFormat::Fasta;
    } else if (format_str == "fastq" || format_str == "fq") {
        ret = SequenceFormat::Fastq;
    } else if (format_str == "sam") {
        ret = SequenceFormat::SAM;
    } else if (format_str == "bam") {
        ret = SequenceFormat::BAM;
    } else if (format_str == "gfa") {
        ret = SequenceFormat::GFA;
    } else if (format_str == "gfa1") {
        ret = SequenceFormat::GFA1;
    } else if (format_str == "gfa2") {
        ret = SequenceFormat::GFA2;
    } else if (format_str == "rdb") {
        ret = SequenceFormat::RaptorDB;
    } else if (format_str == "fofn") {
        ret = SequenceFormat::FOFN;
    } else {
        ret = SequenceFormat::Unknown;
    }
    return ret;
}

inline std::string SequenceFormatToString(const SequenceFormat& fmt) {
    std::string ret("unknown");

    switch(fmt) {
        case SequenceFormat::Auto:
            ret = "auto";
            break;
        case SequenceFormat::Fasta:
            ret = "fasta";
            break;
        case SequenceFormat::Fastq:
            ret = "fastq";
            break;
        case SequenceFormat::SAM:
            ret = "sam";
            break;
        case SequenceFormat::BAM:
            ret = "bam";
            break;
        case SequenceFormat::GFA:
            ret = "gfa";
            break;
        case SequenceFormat::GFA1:
            ret = "gfa1";
            break;
        case SequenceFormat::GFA2:
            ret = "gfa2";
            break;
        case SequenceFormat::RaptorDB:
            ret = "rdb";
            break;
        case SequenceFormat::FOFN:
            ret = "fofn";
            break;
        default:
            ret = "unknown";
    }
    return ret;
}

inline SequenceFormat GetSequenceFormatFromPath(const std::string& path) {
    int32_t pos = path.find_last_of(".");
    std::string ext = path.substr(pos + 1);
    if (ext == "gz") {
        ext = path.substr(path.find_last_of(".", (pos - 1)) + 1);
    }
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    // If the file is Gzipped, the .gz will be in the ext.
    // E.g. the output from GetFileExt can be "fasta.gz".
    if (ext.size() >= 3 && ext.substr(ext.size() - 3) == ".gz") {
        ext = ext.substr(0, ext.size() - 3);
    }
    return SequenceFormatFromString(ext);
}

}

#endif
