# CMakeの最小バージョン
cmake_minimum_required (VERSION 2.4)
# プロジェクト名
project (Chatter) 
# インクルードディレクトリ
include_directories(${PROJECT_SOURCE_DIR} /usr/local/lib/llvm-3.4/include/c++/v1)
# リンクディレクトリ
link_directories(/usr/local/lib/llvm-3.4/usr/lib /Users/kotoji/Library/boost/stage/lib)

# ビルドタイプ
set(CMAKE_BUILD_TYPE Debug)
# コンパイルオプション
set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++ -nostdinc++")

# バイナリの名前とソースファイル 
add_executable (chatter main.cpp client.cpp)
# 
target_link_libraries (chatter boost_system)
