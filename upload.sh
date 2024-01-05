UUID=$1
NDS_FILE=$2

DISK=$(blkid --uuid $UUID)

if [ -z "$DISK" ];
then
    echo "Could not find disk";
    exit 1;
fi

udiskie-mount $DISK || exit 1
cp $2 /run/media/$USER/$UUID/NDS/ || exit 1
udiskie-umount $DISK || exit 1