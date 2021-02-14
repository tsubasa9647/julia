/**********************************************************/
/*       行列計算エンジン ヘッダファイル                  */
/*                                                        */
/* ファイル名：matrix.h                                   */
/* 言語：C++                                              */
/* Ver 1.0 製作者：青葉雅人                               */
/* Ver 1.0 制作日：June 04, 1999                          */
/* 現バージョン  ：1.3.3 beta                             */
/* 改版者        ：青葉雅人                               */
/* 改版日        ：Sep 30, 1999                           */
/**********************************************************/

/***************************************************************************************/
/* 改版履歴                                                                            */
/*                                                                                     */
/* V1.0 beta → V1.1 beta (June 08, 1999)                                              */
/*   クラス Vector にオペレータ += および -= を追加                                    */
/*   クラス Matrix にオペレータ += および -= を追加                                    */
/*   クラス Matrix にオペレータ ^ 追加                                                 */
/*   クラス Matrix に正方行列コンストラクタを追加                                      */
/*   すべてのエラーメッセージを cout から printf に書き換え                            */
/*                                                                                     */
/* V1.1 beta → V1.2 beta (June 23, 1999)                                              */
/*   メンバ関数 Matrix::checkSymmetric を追加                                          */
/*   クラス Vector のコンストラクタ引数のデフォルト値を 0 に書き直し                   */
/*   クラス Matrix のコンストラクタ引数のデフォルト値を 0 に書き直し                   */
/*   クラス Vector のコンストラクタ引数のデフォルト値を 0 に書き直し                   */
/*   メンバ関数 Matrix::print を追加                                                   */
/*   メンバ関数 Vector::print を追加                                                   */
/*   メンバ関数 Vector::row を追加                                                     */
/*   メンバ関数 Vector::col を追加                                                     */
/*   添字演算子を簡略化                                                                */
/*                                                                                     */
/* V1.2 beta → V1.3 beta (June 24, 1999)                                              */
/*   クラス ElementRowVectorOfMatrix を削除                                            */
/*           → クラス Matrix の構成要素を クラス Vector に置き換え                    */
/*                                                                                     */
/* V1.3 beta → V1.3.1 beta (Sep 07, 1999)                                             */
/*   unsigned int をすべて int に書き換え                                              */
/*                                                                                     */
/* V1.3.1 beta → V1.3.2 beta (Sep 30, 1999)                                           */
/*   直接動作と関係しない Warning をすべて排除                                         */
/*                                                                                     */
/* V1.3.2 beta → V1.3.3 beta (Dec 18, 2000)                                           */
/*   正方行列コンストラクタの文字列比較を修正                                          */
/***************************************************************************************/


#ifndef ___MATRIX_H

#define ___MATRIX_H


/* エラーメッセージの表示 */
// #define PRINT_ERROR   // 英語による表示
#define PRINT_ERROR_J // 日本語による表示


/***********************************************/
/* クラスのプロトタイプ                        */
/***********************************************/
class Vector; // ベクトル
class Matrix; // 行列



/***********************************************/
/* Vector                                      */
/*                                             */
/* ベクトルのクラス                            */
/***********************************************/
class Vector
{
	friend Matrix;

protected:
	double *v;              // ベクトルの要素
	int dimension; // ベクトルの次元

public:
	/* コンストラクタ */
	Vector(int d = 0);
	/* コピーコンストラクタ */
	Vector(const Vector& A);
	/* デストラクタ */
	~Vector();

	/* ベクトルを標準出力 */
	virtual void print();

	/* ベクトルを行列に変換 */
	// 行ベクトル
	virtual Matrix row();
	// 列ベクトル
	virtual Matrix col();

	/* 次元数を出力 */
	virtual int dim() { return(dimension); }
	/* 次元数を設定 */
	virtual void setDim(int d);

	/* 代入演算子 */
	Vector& operator=(const Vector& A);

	/* 添字演算子 */
	double& operator[](int i) { return(v[i]); }

	/* ベクトルの演算 */
	// 内積
	friend double operator *(const Vector& A, const Vector& B);
	// 外積
	friend Vector operator &(const Vector& A, const Vector& B);
	// ベクトルとスカラの乗算
	friend Vector operator *(const Vector& A, const double k);
	// スカラとベクトルの乗算
	friend Vector operator *(const double k, const Vector& A);
	// ベクトルとスカラの除算
	friend Vector operator /(const Vector& A, const double k);
	// ベクトルどうしの加算
	friend Vector operator +(const Vector& A, const Vector& B);
	// ベクトルどうしの減算
	friend Vector operator -(const Vector& A, const Vector& B);

	/* 複合代入演算子 */
	// 加算
	Vector& operator +=(Vector& A);
	// 減算
	Vector& operator -=(Vector& A);

	/* ベクトルのノルム */
	virtual double norm();

};


/***********************************************/
/* Matrix                                      */
/*                                             */
/* 行列のクラス                                */
/***********************************************/
class Matrix
{
protected:
	Vector *x;                // 行列を構成する行ベクトル
	int rowDimension, columnDimension; // 行列の行数および列数

public:
	/* コンストラクタ */
	Matrix(int rowDim = 0, int columnDim = 0);
	/* 正方行列コンストラクタ */
	Matrix(int d, char* fg = "zero");
	/* コピーコンストラクタ */
	Matrix(const Matrix& A);
	/* デストラクタ */
	~Matrix();

	/* 行列を標準出力 */
	virtual void print(void);

	/* 行方向の次元 */
	int rdim(void) { return(rowDimension); }
	/* 列方向の次元 */
	int cdim(void) { return(columnDimension); }
	/* 行列の次元を設定 */
	virtual void setDim(int rowDim, int columnDim);

	/* 代入演算子 */
	Matrix& operator=(const Matrix& A);

	/* 添字演算子 */
	Vector& operator[](int i) { return(x[i]); }

	// 列ベクトルを出力
	Vector operator()(int j);

	/* 行列の演算 */
	// 行列どうしの乗算
	friend Matrix operator *(const Matrix& A, const Matrix& B);
	// 行列とスカラの乗算
	friend Matrix operator *(const Matrix& A, const double k);
	// スカラと行列の乗算
	friend Matrix operator *(const double k, const Matrix& A);
	// 行列とスカラの除算
	friend Matrix operator /(const Matrix& A, const double k);
	// 行列を行列（）で除算
	friend Matrix operator /(const Matrix& A, const Matrix& B);
	// 行列どうしの加算
	friend Matrix operator +(const Matrix& A, const Matrix& B);
	// 行列どうしの減算
	friend Matrix operator -(const Matrix& A, const Matrix& B);
	/* べき乗演算子 */
	friend Matrix operator ^(const Matrix& A, const int& k);

	/* 複合代入演算子 */
	// 加算
	Matrix& operator +=(Matrix& A);
	// 減算
	Matrix& operator -=(Matrix& A);


	/* 変換関数（1 x 1 行列 → スカラ） */
	operator double();

	/* 転置 */
	virtual Matrix t();
	friend Matrix trans(Matrix A);
	/* 逆行列 */
	// 掃き出し法
	virtual Matrix inv();
	// 余因子展開
	virtual Matrix invc();

	/* 小行列式 */
	virtual double minorDet(int i, int j);
	/* 余因子 */
	virtual double cofactor(int i, int j);
	/* 行列式 */
	virtual double det();
	friend double det(Matrix A);

	/* トレース */
	virtual double tr();
	friend double tr(Matrix A);

	/* 固有値，固有ベクトルの算出 */
	// 固有値と固有ベクトル
	virtual Matrix eigen(Vector& V);
	// 固有ベクトルのみ
	virtual Matrix eigen();
	// QR法による計算
	virtual Matrix qrEigen(Vector* V);
	// 累乗法による計算
	virtual Matrix powEigen(Vector* V);

	/* ハウスホルダー変換 */
	friend double householder(Matrix* y);
	/* 3重対角化 */
	friend Matrix tridiag(Matrix* A);

	/* upper Hessenberg 行列 への変換 */
	Matrix hessenberg(void);
	Matrix hessenberg2(void);


	/* 対称行列の判定 */
private:
	int checkSymmetric(void);
	Vector qr_dec(void);
	Matrix wielandt(Matrix& A, Vector& V);
	double sgn(double value);
	void lu_dec(Matrix& A, Vector& B, int *id);
	void lu_proxy(Matrix& A, Vector& B);
	void pivot(int k, Matrix& A, Vector& B, int *id);

};


#endif


/* end of file matrix.h */