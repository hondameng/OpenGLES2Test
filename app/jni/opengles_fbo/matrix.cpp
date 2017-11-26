#include "matrix.h"
#include "gl_utils.h"

/**
 * 用于实现矩阵初始化,变换相关函数.
 */
float *getRotateM(float *rm, int rmOffset, float a, float x, float y, float z)
{
  if (rm == NULL)
  {
    rm = (float *) malloc(sizeof(float) * 16);
    memset(rm, 0, sizeof(float) * 16);
  }
  rm[rmOffset + 3] = 0;
  rm[rmOffset + 7] = 0;
  rm[rmOffset + 11] = 0;
  rm[rmOffset + 12] = 0;
  rm[rmOffset + 13] = 0;
  rm[rmOffset + 14] = 0;
  rm[rmOffset + 15] = 1;
  a *= PI / 180.0f;
  float s = (float) sin(a);
  float c = (float) cos(a);
  if (1.0f == x && 0.0f == y && 0.0f == z)
  {
    rm[rmOffset + 5] = c;
    rm[rmOffset + 10] = c;
    rm[rmOffset + 6] = s;
    rm[rmOffset + 9] = -s;
    rm[rmOffset + 1] = 0;
    rm[rmOffset + 2] = 0;
    rm[rmOffset + 4] = 0;
    rm[rmOffset + 8] = 0;
    rm[rmOffset + 0] = 1;
  } else if (0.0f == x && 1.0f == y && 0.0f == z)
  {
    rm[rmOffset + 0] = c;
    rm[rmOffset + 10] = c;
    rm[rmOffset + 8] = s;
    rm[rmOffset + 2] = -s;
    rm[rmOffset + 1] = 0;
    rm[rmOffset + 4] = 0;
    rm[rmOffset + 6] = 0;
    rm[rmOffset + 9] = 0;
    rm[rmOffset + 5] = 1;
  } else if (0.0f == x && 0.0f == y && 1.0f == z)
  {
    rm[rmOffset + 0] = c;
    rm[rmOffset + 5] = c;
    rm[rmOffset + 1] = s;
    rm[rmOffset + 4] = -s;
    rm[rmOffset + 2] = 0;
    rm[rmOffset + 6] = 0;
    rm[rmOffset + 8] = 0;
    rm[rmOffset + 9] = 0;
    rm[rmOffset + 10] = 1;
  } else
  {
    float len = (float) sqrt(x * x + y * y + z * z);
    if (1.0f != len)
    {
      float recipLen = 1.0f / len;
      x *= recipLen;
      y *= recipLen;
      z *= recipLen;
    }
    float nc = 1.0f - c;
    float xy = x * y;
    float yz = y * z;
    float zx = z * x;
    float xs = x * s;
    float ys = y * s;
    float zs = z * s;
    rm[rmOffset + 0] = x * x * nc + c;
    rm[rmOffset + 4] = xy * nc - zs;
    rm[rmOffset + 8] = zx * nc + ys;
    rm[rmOffset + 1] = xy * nc + zs;
    rm[rmOffset + 5] = y * y * nc + c;
    rm[rmOffset + 9] = yz * nc - xs;
    rm[rmOffset + 2] = zx * nc - ys;
    rm[rmOffset + 6] = yz * nc + xs;
    rm[rmOffset + 10] = z * z * nc + c;
  }
  return rm;
}

/**
 * 平移矩阵变换
 */
void translateM (float* m, int mOffset, float x, float y, float z)
{
  if(m == NULL)
    {
      LOGW_MATRIX("translateM() matrix is NULL than do nothing!");
      return;
    }
  for (int i = 0; i < 4; ++i)
    {
      int mi = mOffset + i;
      m[12 + mi] += m[mi] * x + m[4 + mi] * y + m[8 + mi] * z;
    }
}

/**
 * 缩放矩阵变换
 */
void scaleM (float* m, float sx, float sy, float sz)
{
  if(m == NULL)
    {
      LOGW_MATRIX("scaleM() matrix is NULL than do nothing!");
      return;
    }
  m[0]  *= sx;
  m[1]  *= sx;
  m[2]  *= sx;

  m[4]  *= sy;
  m[5]  *= sy;
  m[6]  *= sy;

  m[8]  *= sz;
  m[9]  *= sz;
  m[10] *= sz;
}

/**
 * 获得摄像头视角矩阵
 */
float* setLookAtM (float* rm, int rmOffset, float eyeX, float eyeY, float eyeZ,
	    float centerX, float centerY, float centerZ, float upX, float upY,
	    float upZ)
{
  if (NULL == rm)
    {
      rm = (float*) malloc (sizeof(float) * 16);
      memset (rm, 0, sizeof(float) * 16);
    }
  float fx = centerX - eyeX;
  float fy = centerY - eyeY;
  float fz = centerZ - eyeZ;

  // Normalize f
  float rlf = 1.0f / length (fx, fy, fz);
  fx *= rlf;
  fy *= rlf;
  fz *= rlf;

  // compute s = f x up (x means "cross product")
  float sx = fy * upZ - fz * upY;
  float sy = fz * upX - fx * upZ;
  float sz = fx * upY - fy * upX;

  // and normalize s
  float rls = 1.0f / length (sx, sy, sz);
  sx *= rls;
  sy *= rls;
  sz *= rls;

  // compute u = s x f
  float ux = sy * fz - sz * fy;
  float uy = sz * fx - sx * fz;
  float uz = sx * fy - sy * fx;

  rm[rmOffset + 0] = sx;
  rm[rmOffset + 1] = ux;
  rm[rmOffset + 2] = -fx;
  rm[rmOffset + 3] = 0.0f;

  rm[rmOffset + 4] = sy;
  rm[rmOffset + 5] = uy;
  rm[rmOffset + 6] = -fy;
  rm[rmOffset + 7] = 0.0f;

  rm[rmOffset + 8] = sz;
  rm[rmOffset + 9] = uz;
  rm[rmOffset + 10] = -fz;
  rm[rmOffset + 11] = 0.0f;

  rm[rmOffset + 12] = 0.0f;
  rm[rmOffset + 13] = 0.0f;
  rm[rmOffset + 14] = 0.0f;
  rm[rmOffset + 15] = 1.0f;

  translateM (rm, rmOffset, -eyeX, -eyeY, -eyeZ);
  return rm;
}

//求点之间长度
float length (float x, float y, float z)
{
  return (float) sqrt (x * x + y * y + z * z);
}

/**
 * 4x4矩相乘
 * param left
 */
void matrixMM4 (float* left, float* right)
{
  float* tmp = (float*) malloc (sizeof(float) * 16);
  memset (tmp, 0, sizeof(float) * 16);
  typedef float (*DyadicArray)[4];    //二维数组类型定义
  DyadicArray dLeft = (DyadicArray) left;    //这样强转后,对释放是否有影响.
  DyadicArray dRight = (DyadicArray) right;
  DyadicArray dTmp = (DyadicArray) tmp;
  int i, j, len;
  for (i = 0; i < 4; ++i)
    {
      for (j = 0; j < 4; ++j)
	{
	  float t;
	  t = 0.0f;
	  for (len = 0; len < 4; ++len)
	    {
	      t += (dLeft[i][len] * dRight[len][j]);
	    }
	  dTmp[i][j] = t;
	}
    }
  memcpy (left, dTmp, 16 * sizeof(float));
  free (tmp);
}


float* frustumM (float* m, int offset, float left, float right, float bottom,
	  float top, float near, GLfloat far)
{
  if (NULL == m)
    {
      m = (float*) malloc (sizeof(float) * 16);
      memset(m, 0, sizeof(float) * 16);
    }
  if (left == right)
    {
      LOGW_MATRIX("frustumM() left == right!!!");
    }
  if (top == bottom)
    {
      LOGW_MATRIX("frustumM() top == bottom!!!");
    }
  if (near == far)
    {
      LOGW_MATRIX("frustumM() near == far!!!");
    }
  if (near <= 0.0f)
    {
      LOGW_MATRIX("frustumM() near <= 0.0f!!! near = %lf", near);
    }
  if (far <= 0.0f)
    {
      LOGW_MATRIX("frustumM() far <= 0.0f!!! far = %lf", far);
    }
  float r_width = 1.0f / (right - left);
  float r_height = 1.0f / (top - bottom);
  float r_depth = 1.0f / (near - far);
  float x = 2.0f * (near * r_width);
  float y = 2.0f * (near * r_height);
  float A = (right + left) * r_width;
  float B = (top + bottom) * r_height;
  float C = (far + near) * r_depth;
  float D = 2.0f * (far * near * r_depth);
  m[offset + 0] = x;
  m[offset + 5] = y;
  m[offset + 8] = A;
  m[offset + 9] = B;
  m[offset + 10] = C;
  m[offset + 14] = D;
  m[offset + 11] = -1.0f;
  m[offset + 1] = 0.0f;
  m[offset + 2] = 0.0f;
  m[offset + 3] = 0.0f;
  m[offset + 4] = 0.0f;
  m[offset + 6] = 0.0f;
  m[offset + 7] = 0.0f;
  m[offset + 12] = 0.0f;
  m[offset + 13] = 0.0f;
  m[offset + 15] = 0.0f;
  return m;
}