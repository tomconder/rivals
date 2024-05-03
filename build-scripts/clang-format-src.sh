#!/bin/sh

pushd . > /dev/null
cd "../game/src"
echo "Running clang-format in $(pwd)"
find . -regex '.*\.[chm]p*' -exec clang-format -i {} \;
popd > /dev/null

echo "clang-format complete!"
