/*
 * mapping_base.h
 *
 *  Created on: Dec 3, 2017
 *      Author: Ivan Sovic
 */

#ifndef SRC_CONTAINERS_MAPPING_BASE_H_
#define SRC_CONTAINERS_MAPPING_BASE_H_

#include <cstdint>
#include <vector>
#include <unordered_map>
#include <aligner/cigar.h>

namespace raptor {

class RegionExtraTags {
    public:
    // // The "name" can be used to identify this tag more verbosely, or to
    // // display in more verbose formats.
    // std::string name;

    // The following three fields should be consistentwith SAM/BAM conventions.
    // They can simply be joined with a ':', and they would automatically be
    // compliant with the SAM/BAM formats.

    // The SAM/BAM compliant naming. It should include the data type too. E.g. cg:z
    std::string id;
    // The SAM/BAM compliant naming of a tag type. E.g. i for integer.
    std::string type;
    // Values packed in a string, regardless of the underlying data type, for simplicity.
    std::string val;
};

/*
 * RegionBase provides the base interface for both mapping and alignment results.
 * It's intention is to provide an unified interface for accessing information
 * required to write any of the output formats (SAM, MHAP, PAF, etc.).
*/
class RegionBase {
public:
    virtual ~RegionBase() {
    }

    virtual int32_t QueryID() const = 0;
    virtual bool QueryRev() const = 0;
    virtual int32_t QueryStart() const = 0;
    virtual int32_t QueryEnd() const = 0;
    virtual int32_t QueryLen() const = 0;
    virtual int32_t QuerySpan() const = 0;
    virtual int32_t TargetID() const = 0;
    virtual bool TargetRev() const = 0;
    virtual int32_t TargetStart() const = 0;                    // TargetStart() is in the strand of alignment and 0-based.
    virtual int32_t TargetEnd() const = 0;                      // TargetEnd() is in the strand of alignment, 0-based, and non-inclusive (1 base after the last inclusive position).
    virtual int32_t TargetLen() const = 0;
    virtual int32_t TargetSpan() const = 0;
    virtual int32_t TargetIndexStart() const = 0;
    virtual int32_t TargetFwdStart() const = 0;                 // TargetFwdStart() corresponds to the start coordinate in the FWD strand of the sequence.
    virtual int32_t TargetFwdEnd() const = 0;                   // TargetFwdEnd() corresponds to the end coordinate in the FWD strand of the sequence.
    virtual int32_t Score() const = 0;
    virtual int32_t NumSeeds() const = 0;
    virtual int32_t CoveredBasesQuery() const = 0;
    virtual int32_t CoveredBasesTarget() const = 0;
    virtual int32_t EditDistance() const = 0;
    virtual std::vector<raptor::CigarOp> Cigar() const = 0;
    virtual bool IsPrimary() const = 0;
    virtual bool IsSecondary() const = 0;
    virtual bool IsSupplementary() const = 0;

    // The following keep track of the number of alternative alignments.
    // If PathId() == 0, this is the primary alignment, otherwise secondary.
    // These should strictly be used for output, and can contain any value.
    virtual int32_t PathId() const = 0;         // Current alignment/mapping ID.
    virtual int32_t PathsNum() const = 0;       // Total number of alternative paths.
    virtual int32_t SegmentId() const = 0;      // ID of the supplementary alignment.
    virtual int32_t SegmentsNum() const = 0;    // Number of supplementary alignments for the path.

    // If there is any additional data which needs to be available for output, it
    // can be encoded here.
    virtual const std::unordered_map<std::string, raptor::RegionExtraTags>& ExtraTags() const = 0;

    virtual std::string WriteAsCSV(const char separator) const = 0;

    ////////////////
    /// Setters. ///
    ////////////////
    virtual void SetCoveredBasesQuery(int32_t val) = 0;
    virtual void SetCoveredBasesTarget(int32_t val) = 0;
    virtual void SetEditDistance(int32_t val) = 0;
    virtual void SetScore(int32_t val) = 0;
    virtual void AddTag(const raptor::RegionExtraTags& val) = 0;
};

}

#endif
