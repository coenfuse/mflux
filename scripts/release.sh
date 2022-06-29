# TODO - The following ROOT will not work if this script is invoked from outside
# of the scripts folder because we have '../' here

# Getting root directory for relative operations (one dir back /scripts)
ROOT="$PWD/../"

# Clearing the release folder for any packages
rm -r $ROOT/out/rel/

# Creating general folder structure
mkdir $ROOT/out/rel
mkdir $ROOT/out/rel/pkg
mkdir $ROOT/out/rel/bld

PKG_PATH="$ROOT/out/rel/pkg"
BLD_PATH="$ROOT/out/rel/bld"

# Creating package folder structure
mkdir $PKG_PATH/app
mkdir $PKG_PATH/config
# mkdir $PKG_PATH/dat
# mkdir $PKG_PATH/etc
mkdir $PKG_PATH/out

# Build project files
cmake -B $BLD_PATH -S $ROOT -DCMAKE_BUILD_TYPE=Release -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY=$BLD_PATH/obj -DCMAKE_LIBRARY_OUTPUT_DIRECTORY=$PKG_PATH/app/lib -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=$PKG_PATH/app

# Build binaries
cmake --build $BLD_PATH

# Copying files
cp $ROOT/config/mflux.config.jsonc $PKG_PATH/config
cp $ROOT/dat/relpkg/readme.txt $PKG_PATH
cp $ROOT/dat/relpkg/start.sh $PKG_PATH

# Creating zip (The 'cd' helps in creating a zip without any root folder)
cd $PKG_PATH
zip -r ../mflux.zip .                                                           

# Cleaning up
rm -r $BLD_PATH
rm -r $PKG_PATH
touch $ROOT/out/rel/pkg