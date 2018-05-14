#!/bin/bash

equal=0
empty=0
total=0
while read line
do
    storehouseId=`echo $line | cut -d',' -f'1'`
    express=`echo $line | cut -d',' -f'2'`
    districtName=`echo $line | cut -d',' -f'3'`
    sentence="select DistrictId from TB_YX_SMARTIPC_AREA_DISTRICT where DistrictName=\"${districtName}\";"
    DistrictId=`mysql -u root -proot yanxuan_smartipc -e "${sentence}"`
    DistrictId=`echo $DistrictId | cut -d' ' -f2`

    sentence="select ExpCompanyCode from TB_YX_SMARTIPC_EXPRESS_DISTRICT_SETTING where DistrictId=\"${DistrictId}\" and StoreHouseId=\"${storehouseId}\" and ExpressDistrictSettingType=0;"
    queryResult=`mysql -u root -proot yanxuan_smartipc -e "$sentence"`
    queryResult=`echo $queryResult | cut -d' ' -f2`

    total=$(($total+1))
    echo $express, $queryResult, $total
    if [ $express = $queryResult ]; then
        equal=$(($equal+1))
    elif [ "a$queryResult" = 'a' ]; then
        empty=$(($empty+1))
    fi
done < /tmp/data

echo $total, $equal, $empty
