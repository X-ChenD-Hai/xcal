/**
 * @file paths.hpp
 * @author X_Chen D_Hai (illuminatestar@foxmail.com)
 * @brief This file contains the declaration of paths used in xcal.
 * @version 0.1
 * @date 2025-09-07
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <string>

namespace xcal::utils::paths {
/**
 * @brief Get the current working directory.
 *
 */
extern const std::string CURRENT_WORKING_DIRECTORY;
/**
 * @brief Get the path of the executable.
 *
 */
extern const std::string EXECUTABLE_PATH;
/**
 * @brief Get the directory of the executable.
 *
 */
extern const std::string EXECUTABLE_DIR;
}  // namespace xcal::utils::paths