#ifndef _COORTRANS_H_INCLUDED
#define _COORTRANS_H_INCLUDED

const double PI = 3.14159265353846;
class PrjPoint
{
	private:
		double m_OriginLongitude; // 中央子午线经度
		double m_Lo, m_La; // 经纬度坐标
		double x, y; // 高斯投影平面坐标
		double m_ZoneNum;//工作区带号
		double m_ParaDegree;//分段度数
		int m_CoordSysType;//标准类型(0为克鲁索夫斯基标准，1为国家UGG1975标准,2为WGS84椭球体)
	private:
		bool SetOriginLongitude(double dOriginLongitude);// 设置中央子午线经度
		bool LoLaToxy();//经纬度坐标转为大地坐标
		bool xyToLoLa();//大地坐标转为经纬度坐标
		bool SetTempxy(double dx, double dy);//设置大地坐标
	protected:
		double a,b,n, f, e2, e12; // 基本椭球参数,a长半径,b短半径,n=(a-b)/(a+b),f扁率,e2第一偏心率平方,e12第二偏心率平方
		double A1, A2, A3, A4; // 用于计算X的椭球参数 
	public:
		PrjPoint();
		~PrjPoint();
	public:
		bool SetCoordSysType(int type);//设置标准椭球体类型,默认为0(0为克鲁索夫斯基椭球体，1为国家UGG1975椭球体,2为WGS84椭球体)
		bool SetAB(double da,double db);//设置其他椭球体;da和db为椭球体的长半径和短半径
		bool SetParaDegree(double ParaDegree);//设置分段度数,默认为6度
		bool SetZoneNum(double ZoneNum);//设置工区带号,默认为21带
		bool SetLoLa(double dLo, double dLa);//设置经纬度坐标
		bool GetLoLa(double *dLo, double *dLa);//得到经纬度坐标
		bool Setxy(double dx, double dy);//设置大地坐标
		bool Getxy(double *dx, double *dy);//得到大地坐标
		bool GetSpaceCoord(double *dx, double *dy,double *dz);//得到空间坐标
};
double Dms2Rad(double Dms);//角度到弧度的转化
double Rad2Dms(double Rad);//弧度到角度的转化
double calDist(double la1, double lo1, double la2, double lo2);//根据两点经纬度计算两点之间的直线距离
#endif /* ndef _COORTRANS_H_INCLUDED */
