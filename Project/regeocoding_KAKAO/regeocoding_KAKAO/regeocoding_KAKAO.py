import json
import sys
import pandas as pd
import requests
from datetime import *
from tqdm import notebook
import time
import numpy as np
import pyproj
import folium
import os

# 전역 변수
APP_KEY = '405a10eecf1095fd9c4a61d6774cf3ae'    # 발급받은 키 입력
URL = 'https://dapi.kakao.com/v2/local/geo/coord2address.json'
URL2= 'https://dapi.kakao.com/v2/local/geo/transcoord.json'
# WTM, TM, 

def json_request(url='', encoding='utf-8', success=None, error=lambda e: print('%s : %s' % (e, datetime.now()), file=sys.stderr)):
    headers = {'Authorization': 'KakaoAK {}'.format(APP_KEY)}

    resp = requests.get(url, headers=headers)
    print(resp)
    print('%s : success for request [%s]' % (datetime.now(), url


    return resp.json()
    
def reverse_geocode(longitude, latitude, s_dataType):
   
    if s_dataType == 'WTM' :
        url2 = '%s?x=%s&y=%s&input_coord=%s&output_coord=WGS84' %(URL2, longitude, latitude, s_dataType)
        json_req = json_request(url=url2)
        json_doc = json_req.get('documents')[0]
        url = '%s?x=%s&y=%s&input_coord=WGS84' %(URL, round(json_doc.get('x'),6), round(json_doc.get('y'),6))
    elif s_dataType == 'WGS84' :
        url = '%s?x=%s&y=%s&input_coord=%s' %(URL, longitude, latitude, s_dataType)


    print(url)
    # json request
    try:
        json_req = json_request(url=url)
        print(json_req)
        json_doc = json_req.get('documents')[0]
        json_name = json_doc.get('address').get('address_name')
    except:
        json_name = 'NaN'

    return json_name
    
    
def get_address(url_csv, dataType):
    p1_type = 'epsg:2097'
    p2_type = 'epsg:4326'
    address = []
    url_csv['x'] = pd.to_numeric(url_csv['x'], errors='coerce')
    url_csv['y'] = pd.to_numeric(url_csv['y'], errors='coerce')

    # url_csv = url_csv.dropna()
    #url_csv.index=range(len(url_csv))
    #url_csv.tail()
    # 경도, 위도 추출해서 동 주소 반환
    if dataType == '1':
        s_dataType = 'WTM'
    else :
        s_dataType = 'WGS84'

    result = np.array(url_csv)
    for i in notebook.tqdm(url_csv.index) :
        longitude = result[i][0]
        latitude  = result[i][1]
        address.append(reverse_geocode(longitude, latitude, s_dataType))
      
    
    #print(address)
    return address  # 전처리 함수에서 주소 리스트 받아서 데이터프레임에 추가

"""
def project_array(coord, p1_type, p2_type):
    
    좌표계 변환 함수
    - coord: x, y 좌표 정보가 담긴 NumPy Array
    - p1_type: 입력 좌표계 정보 ex) epsg:5179
    - p2_type: 출력 좌표계 정보 ex) epsg:4326
    
    p1 = pyproj.Proj(init=p1_type)
    p2 = pyproj.Proj(init=p2_type)
    fx, fy = pyproj.transform(p1, p2, coord[:, 0], coord[:, 1])
    return np.dstack([fx, fy])[0]
"""

def main():
  
    path = os.path.dirname(os.path.abspath(__file__))
    #print(path)
    # 파일 읽기
    print("===================== 영민이를 위한 주소 추출 프로그램 =====================")
    
    print("1. TM 좌표계 방식(ex.192085.702260    182111.703093)")
    print("2. WGS84 좌표계 방식(ex.126.911078	35.138094)")
    dataType = input("input 좌표의 데이터 형식을 선택해주세요 : ")
    if dataType != '1' and dataType != '2' :
        print("이상한 값 넣으면 안됩니다..")
        return 0;

    start = time.time()
    url_csv = pd.read_csv('target.csv',encoding='cp949',usecols=['x','y'])
    url_csv2 = pd.read_csv('target.csv',encoding='cp949')
#     url_csv_5 = url_csv.head()
    
    address = get_address(url_csv, dataType)
 
  
    dong=pd.DataFrame(address)   
    dong.columns=['주소']
    url_csv2['주소']=address
   
    url_csv2.to_csv(r'result.csv',encoding='utf-8')
    print("time :", time.time() - start)
    
 
if __name__ == '__main__':
    main()
