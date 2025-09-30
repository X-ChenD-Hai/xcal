
function(xcal_add_library NAME IDENT)
    set(CONFIG_DIR ${CMAKE_SOURCE_DIR}/tools)
    configure_file(${CONFIG_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/${NAME}_config.h)
    if(BUILD_DYNAMIC_LIBRARY)
        add_library(${NAME} SHARED)
        message(STATUS "[XCAL] configuring dynamic library ${NAME}")
        target_compile_definitions(${NAME}
            PUBLIC ${IDENT}_ENABLE_DYNAMIC_LIBRARY
            PRIVATE ${IDENT}_BUILD
        )
        if(BUILD_EXAMPLES)
            add_custom_command(
                TARGET ${NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:${NAME}>
                ${CMAKE_BINARY_DIR}/examples
                COMMENT "Copying ${NAME} to examples directory"
            )
        endif()
    else()
        message(STATUS "[XCAL] configuring static library ${NAME}")
        add_library(${NAME} STATIC)
    endif()
    target_compile_definitions(${NAME} PUBLIC
        PUBLIC ${IDENT}_CONFIG_HEADER=<${CMAKE_CURRENT_BINARY_DIR}/${NAME}_config.h>
    )
endfunction(xcal_add_library)
