cmake_minimum_required(VERSION 2.8)

include_directories(
		../src
)

find_package(CURL)
if (CURL_FOUND)
   set(grabber_libs ${grabber_libs}
   					${CURL_LIBRARIES}
					)
endif(CURL_FOUND)
