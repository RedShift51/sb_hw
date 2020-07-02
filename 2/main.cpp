#include <iostream>
#include <algorithm>

struct info
{
    int x0, y0;
    int sizeX, sizeY;
};

template <typename T>
class Matrix
{
public:

    Matrix () : array(), blocks(), aux_buff()
    {
        this->sizeX = 0;
        this->sizeY = 0;
        this->sizeBlocks = 0;
        this->sizeBuff = 0;
    }

    Matrix (int sizeX, int sizeY, int sizeBlocks, int sizeBuff) :
        sizeX(sizeX), sizeY(sizeY), sizeBlocks(sizeBlocks), sizeBuff(sizeBuff)
    {
        array = new T[this->sizeX * this->sizeY];
        blocks = new info[this->sizeBlocks];
        aux_buff = new T[this->sizeBuff];
    }

    void copy_array(const T * src, T * dst, int size)
    {
        for (int i = 0; i < size; i++)
        {
            dst[i] = src[i];
        }
    }

    void copy_array_info(const info* src, info* dst, int size)
    {
        for (int i = 0; i < size; i++)
        {
            dst[i] = src[i];
        }
    }

    Matrix (const Matrix& other)
    {
        
        /* Copying array */
        if (other.array)
        {
            array = new T[other.sizeX * other.sizeY];
            copy_array(other.array, array, other.sizeX * other.sizeY);
            sizeX = other.sizeX;
            sizeY = other.sizeY;
        } else {
            sizeX = 0;
            sizeY = 0;
        }

        /* Copying other fields */
        if (other.blocks)
        {
            blocks = new info[other.sizeBlocks];
            copy_array_info(other.blocks, blocks, other.sizeBlocks);
            sizeBlocks = other.sizeBlocks;
        } else {
            sizeBlocks = 0;
        }

        if (other.aux_buff)
        {
            aux_buff = new T[other.sizeBuff];
            copy_array(other.aux_buff, aux_buff, other.sizeBuff);
            sizeBuff = other.sizeBuff;
        } else {
            sizeBuff = 0;
        }
    }

    ~Matrix ()
    {
        if (array) delete[] array;
        if (blocks) delete[] blocks;
        if (aux_buff) delete[] aux_buff;
    }

    Matrix& operator=(Matrix& other)
    {
        if (array) delete[] array; 
        if (other.array)
        {
            array = new T[other.sizeX * other.sizeY];
            copy_array(other.array, array, other.sizeX * other.sizeY);
            sizeX = other.sizeX;
            sizeY = other.sizeY;
        } else {
            sizeX = 0;
            sizeY = 0;
        }

        /* Copying other fields */
        if (blocks) delete[] blocks;
        if (other.blocks)
        {
            blocks = new info[other.sizeBlocks];
            copy_array_info(other.blocks, blocks, other.sizeBlocks);
            sizeBlocks = other.sizeBlocks;
        } else {
            sizeBlocks = 0;
        }

        if (aux_buff) delete[] aux_buff;
        if (other.aux_buff)
        {
            aux_buff = new T[other.sizeBuff];
            copy_array(other.aux_buff, aux_buff, other.sizeBuff);
            sizeBuff = other.sizeBuff;
        } else {
            sizeBuff = 0;
        }

        return (*this);        
    }

    T& get(const int index_i, const int index_j)
    {
        return array[sizeX * index_i + index_j];
    }

private:
    int sizeX, sizeY;
    T* array;

    int sizeBlocks;
    info* blocks;

    int sizeBuff;
    T* aux_buff;
};

int main()
{
    Matrix<float> a(10, 10, 10, 10);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            a.get(i, j) = (i + j) % 10;
        }
    }

    Matrix<float> b(a);

    Matrix<float> c;
    c = b;

    std::cout << a.get(7, 7) << " " << b.get(7, 7) << " "
                << c.get(7, 7) << std::endl;
    return 0;
}
