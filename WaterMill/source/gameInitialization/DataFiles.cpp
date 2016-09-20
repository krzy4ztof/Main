/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   DataFiles.cpp
 * Author: Krzysztof
 *
 * Created on 30 kwietnia 2016, 12:48
 */

#include "DataFiles.h"
#include "ErrorCode.h"

namespace watermill {

	namespace data_files {
		void safe_delete(DataFiles* p) {
			if (p) {
				delete (p);
				(p)=nullptr;
			}
		}
	}

	DataFiles::DataFiles() {
		// Initialization
		bool somethingWentWrong = false;

		if (somethingWentWrong) {
			throw ErrorCode("EC_DATAFILES_PROBLEM", 789);
		}
	}

	DataFiles::DataFiles(const DataFiles& orig) {
	}

	DataFiles::~DataFiles() {
	}

}
