/*
 * params_raptor_fetch.h
 *
 *  Created on: Dec 22, 2017
 *      Author: Ivan Sovic
 *
 * Raptor-fetch is intended to perform random access to the Raptor DB.
 * reshape the input data.
 */

#ifndef SRC_RAPTOR_PARAMS_RAPTOR_FETCH_H_
#define SRC_RAPTOR_PARAMS_RAPTOR_FETCH_H_

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace raptor {

class ParamsRaptorFetch;

std::shared_ptr<raptor::ParamsRaptorFetch> createParamsRaptorFetch();

class ParamsRaptorFetch {
   public:
    friend std::shared_ptr<raptor::ParamsRaptorFetch> createParamsRaptorFetch();
    ~ParamsRaptorFetch() = default;

    /*
      Command-line related options.
    */
    std::string subprogram = "";
    std::string command_line = "";

    int64_t verbose_level;
    std::string in_path;

   private:
    ParamsRaptorFetch();
    ParamsRaptorFetch(const ParamsRaptorFetch&) = delete;
    ParamsRaptorFetch& operator=(const ParamsRaptorFetch&) = delete;
};

}  // namespace raptor

#endif /* SRC_RAPTOR_PARAMS_RAPTOR_INDEX_H_ */
