/********************************************************************************
* ##########  ̸̸��װ ##########
* ����װ���ǳ��򲻻��ҵ���һ����Ҫ���ܡ�
* ����Ҫд���ṹ���������Ķ��������ά���Ĵ��롣���÷�װ�ǱȽ��������յķ�����
*
* ������ԣ�
*
* 1���ȿ��Ǻ����������߼���״̬��Ҫ������������ʾ��
* �������̰������Ϸ������ʹ����Щ���ݾͿ��Ա�ʾȫ����Ϸ״̬��
* // ʳ��
* GAME_COORD food;
* // �ߣ�������
* PLIST snake_list;
* // ���ƶ�����
* dirction snake_dir;
* // ��Ϸ�߽磨�������£�����Ϊ0,0��
* GAME_COORD boundary;
*
* 2��д��һϵ�нӿں�����������Щ���ݡ���ν�ӿں���������һ�¼���������
* (1) ��Щ���ݳ��˽ӿں������⣬�������붼����ֱ�ӷ��ʡ�
* (2) �����������붼ֻ��ͨ��������Щ�ӿں������ı�����״̬������Ҫֱ��ȥ�������ݡ�
* �籾�ļ������ɺ������Ƕ��������ݵĲ�����

* ����ʵ���ˣ������ϲ���룬������Ҫ֪�����ݵĲ����߼���Ҳ����Ҫ֪�����ݽṹ����ֻ��Ҫ���ú������ɡ�
* ���ϴδ�����ԣ��߼����˺ܶࡣ
* ͬ����������ݽṹ���ڲ��߼������޸ģ���ô���������ӿں�����ԭ�Ͳ��䣬
* �ϲ���벻�䣬��ֻ��Ҫ�޸Ľӿں������ڲ�ʵ�ֹ��̼��ɡ�
*
* ��ͳ�֮Ϊ����װ�������߳�֮Ϊ �����ݵķ�װ�ͽӿڻ���
*
*******************************************************************************/



/************** ͷ�ļ� ****************/
#include "snake.h"

/************* ȫ�ֱ��� ****************/ //��Ϸ��������ȫ�ֱ���  
// ʳ��
PGAME_COORD food[2];
//��ҩ
PGAME_COORD drug[18];
// �ߣ�������
PLIST snake_list;
// ���ƶ�����
dirction snake_dir;
// ��Ϸ�߽磨�������£�����Ϊ0,0��
GAME_COORD boundary;

/*********** �ڲ��������� **************/
/// �ж����������Ƿ���ȡ�
int CoordEqual(PGAME_COORD one, PGAME_COORD two);
/// �ж����Ƿ�����
int IsSnakeDead();

/**************��������****************/


// �ж��������� GAME_COORD �Ƿ��غ�
int CoordEqual(PGAME_COORD one, PGAME_COORD two)
{
	if (one->x == two->x && one->y == two->y)//����һ��������ǲ���������ȣ������ͬ���൱����ҧ���Լ���β�� zbj
		return 1;
	return 0;
}

// ���ñ߽�����
void SetBoundary(int x, int y)
{
	boundary.x = x;
	boundary.y = y;
}

// ��ñ߽�����
PGAME_COORD GetBoundary()
{
	return &boundary;//��ָ�봫�ݱ߽磨�߽����½����꣩zbj
}

// �����µ�ʳ�
int CreateFood()
{
	PGAME_COORD posbody;//����ʳ������ zbj//����һ��������ϵ �Ⱥ������ص��Ӱ��
	int i,j;//ѭ�������� zbj
	int size = ListSize(snake_list);//��ȡ�ߵĳ��ȣ�boundary�������½ǵĵ�
	food[0] = (PGAME_COORD)malloc(sizeof(PGAME_COORD));
	food[1] = (PGAME_COORD)malloc(sizeof(PGAME_COORD));
new_food://�е���python

	// �������ʳ������ꡣ
	food[0]->x = rand() % boundary.x;//��Ϊ�˱�֤��ȡ��λ���ڴ����ڲ�����Ϊ�п������ɵ����ȴ��ڷ�Χ�� zbj
	food[0]->y= rand() % boundary.y;//%������ȡ�ض���Χ�����������֤������ƽ���ֲ��� ��%100���������ķ�Χ��0-99
	food[1]->x = rand() % boundary.x;
	food[1]->y = rand() % boundary.y;

	// �ж��Ƿ�����ص��ˣ�������������ʳ�����֪꣬�����ص���

	for (i = 0; i < size; i++)//ѭ����ȡ�������ڵ������ zbj//ȡ�ߵ�ÿ����������   zbjk
	{
		posbody = (PGAME_COORD)ListGetAt(snake_list, i);//��ȡ�����ݽ��������ڵ㵱ǰ������ zbj
		for (j = 0; j < 2; j++) {
			if (CoordEqual(posbody, food[j]))//���ʳ����������ȡ�ڵ��������ȣ���ô����������ʳ������� zbj
			{
				goto new_food;//�ǳ����ϵ��﷨����Ӱ��,������˶�����һ����ǩ������˵λ�ã����ͻ���ת��ȥִ�б�ǩ������ѭ���Ĺ��� zbj
			}//��goto���÷�    zbj//ֻҪ������������λ���ظ�������������
		}
	}
	return 1;//93--100�����ж�ʳ���ǲ������ߵ����ϣ�����غϾ�����һ���µ�ʳ��λ�� zbj

}
//�����µĶ�ҩ��

int CreateDrug()
{
	PGAME_COORD posbody;//���嶾ҩ���� zbj//����һ��������ϵ �Ⱥ������ص��Ӱ��
	int i, j,k;//ѭ�������� zbj
	int size = ListSize(snake_list);//��ȡ�ߵĳ��ȣ�boundary�������½ǵĵ�
	for (i = 0; i < 18; i++)
	{
		drug[i] = (PGAME_COORD)malloc(sizeof(PGAME_COORD));
		
	}
	new_drug://�е���python

		// ������ɶ�ҩ�����ꡣ
	for (i = 0; i < 18; i++)
	{
		drug[i]->x = rand() % boundary.x;//��Ϊ�˱�֤��ȡ��λ���ڴ����ڲ�����Ϊ�п������ɵ����ȴ��ڷ�Χ�� zbj
		drug[i]->y = rand() % boundary.y;//%������ȡ�ض���Χ�����������֤������ƽ���ֲ��� ��%100���������ķ�Χ��0-99
		
	}
	// �ж��Ƿ�����ص��ˣ������������ɶ�ҩ���֪꣬�����ص���

	for (k = 0; k < 18; k++)//ѭ����ȡ�������ڵ������ zbj//ȡ�ߵ�ÿ����������   zbjk
	{
		
		for (j = 0; j < 2; j++)
		{
			for (i = 0; i < size; i++)//ѭ����ȡ�������ڵ������ zbj//ȡ�ߵ�ÿ����������   zbjk
			{
				posbody = (PGAME_COORD)ListGetAt(snake_list, i);//��ȡ�����ݽ��������ڵ㵱ǰ������ zbj
				if (CoordEqual(posbody, drug[k]) || CoordEqual(food[j],drug[k]))//���ʳ����������ȡ�ڵ��������ȣ���ô����������ʳ������� zbj
				{
					goto new_drug;//�ǳ����ϵ��﷨����Ӱ��,������˶�����һ����ǩ������˵λ�ã����ͻ���ת��ȥִ�б�ǩ������ѭ���Ĺ��� zbj
				}//��goto���÷�    zbj//ֻҪ������������λ���ظ�������������
			}
		}
	}
		return 1;//�����ж϶�ҩ�ǲ������ߵ����ϣ�����غϾ�����һ���µĶ�ҩλ�� zbj

	}


// �ֱ�������ʳ������ꡣ
PGAME_COORD GetFood1()
{
	return food[0];//����ʳ���ָ�� zbj
}
PGAME_COORD GetFood2()
{
	return food[1];//����ʳ���ָ�� zbj
}
//�ֱ������Ŷ�ҩ�����ꡣ
PGAME_COORD GetDrug1()
{
	return drug[0];//���ض�ҩ��ָ�� zbj
}

PGAME_COORD GetDrug2()
{
	return drug[1];//���ض�ҩ��ָ�� zbj
}

PGAME_COORD GetDrug3()
{
	return drug[2];//���ض�ҩ��ָ�� zbj
}

PGAME_COORD GetDrug4()
{
	return drug[3];//���ض�ҩ��ָ�� zbj
}

PGAME_COORD GetDrug5()
{
	return drug[4];//���ض�ҩ��ָ�� zbj
}

PGAME_COORD GetDrug6()
{
	return drug[5];//���ض�ҩ��ָ�� zbj
}

PGAME_COORD GetDrug7()
{
	return drug[6];//���ض�ҩ��ָ�� zbj
}

PGAME_COORD GetDrug8()
{
	return drug[7];//���ض�ҩ��ָ�� zbj
}

PGAME_COORD GetDrug9()
{
	return drug[8];//���ض�ҩ��ָ�� zbj
}

PGAME_COORD GetDrug10()
{
	return drug[9];//���ض�ҩ��ָ�� zbj
}

PGAME_COORD GetDrug11()
{
	return drug[10];//���ض�ҩ��ָ�� zbj
}

PGAME_COORD GetDrug12()
{
	return drug[11];//���ض�ҩ��ָ�� zbj
}

PGAME_COORD GetDrug13()
{
	return drug[12];//���ض�ҩ��ָ�� zbj
}

PGAME_COORD GetDrug14()
{
	return drug[13];//���ض�ҩ��ָ�� zbj
}

PGAME_COORD GetDrug15()
{
	return drug[14];//���ض�ҩ��ָ�� zbj
}

PGAME_COORD GetDrug16()
{
	return drug[15];//���ض�ҩ��ָ�� zbj
}

PGAME_COORD GetDrug17()
{
	return drug[16];//���ض�ҩ��ָ�� zbj
}

PGAME_COORD GetDrug18()
{
	return drug[17];//���ض�ҩ��ָ�� zbj
}
// ������
void CreateSnake(dirction dir, int head_x, int head_y, int init_len)//�߳�ʼ���򣬳�ʼλ�ã���ʼ���ȡ�Ϊʲô����ÿ���ڵ��أ���ʵ��������ڵ�λ�ã���ʼ����Ҫײ��ǽ
{//��һ���ӽڵ�
	PGAME_COORD p;//��ʼ����ͷλ������ zbj
	int i;//ѭ�������� zbj

	SetDirction(dir);//����Ҫ���趨�ߵĳ�ʼ���� zbj

	snake_list = ListCreate(NULL);//����һ���µ�����snake_list????? zbj

	p = (PGAME_COORD)malloc(sizeof(GAME_COORD));//��p�����ڴ� zbj
	// ��ͷ���ĳ�ʼλ�ã�
	p->x = head_x;//������ͷ�ڵ��λ�ô�����ͷ�ĳ�ʼλ�ã�����һ��ѭ�� zbj
	p->y = head_y;
	ListPushFront(snake_list, p);//��p�ŵ�����snake_list��   zbjk//ʵ�����ߵ�ͷ�ڵ�??????�Ľ�����ͷ�ڵ���һ���ڵ������������ͷ����λ��?????  zbj

	for (i = 1; i < init_len; i++)//����ߵĽڵ㳤�ȴ��ڵ���0���������ߵĳ��ȣ������趨�����ķ���  zbj
	{
		//p = (PGAME_COORD)malloc(sizeof(GAME_COORD));
		SnakeGorwup();//�������ĺ���
	}
	return;
}

// �ж����Ƿ����ˡ�
// ����0 ��û���� else �����ˡ�
int IsSnakeDead()//��Ҫ����߽�
{
	PGAME_COORD posBody;//����λ��ָ��  zbj
	PGAME_COORD posHead;

	int i;
	int size = ListSize(snake_list);//��ȡ�������ĳ���  zbj

	// �ж��Ƿ�����
	/// ����ǽ��������������
	posHead = (PGAME_COORD)ListGetAt(snake_list, 0);//ȡ��������ͷ�ڵ��λ��ָ��  zbj
	size = ListSize(snake_list);////��ȡ�������ĳ���  zbj
	if (posHead->x < 0 || posHead->x > boundary.x ||
		posHead->y < 0 || posHead->y > boundary.y)//�ǲ���ͷ��λ��С��0����ڱ߽�  x,y�κγ����߽� zbj
	{//Ҫ�޸�ȫ���ڵ��λ��

		if (posHead->x < 0)//����ǽ���Ľڵ�������Ҵ���
			for (i = 0; i < size; i++)
			{
				posBody = (PGAME_COORD)ListGetAt(snake_list, i);//ȡ�������ĵ�i���ڵ��λ��ָ��   zbj
				posBody->x = boundary.x - ListSize(snake_list) + 1+i;
			}
			
		if (posHead->x > boundary.x)//���Ҵ�ǽ���Ľڵ����������
			for (i = 0; i < size; i++)
			{
				posBody = (PGAME_COORD)ListGetAt(snake_list, i);
				posBody->x = ListSize(snake_list) - 1 - i;
			}
			
		if (posHead->y < 0)//���ϴ�ǽ���Ľڵ�������´���
			for (i = 0; i < size; i++)
			{
				posBody = (PGAME_COORD)ListGetAt(snake_list, i);
				posHead->y = boundary.y - ListSize(snake_list) + 1 + i;
			}
		if (posHead->y > boundary.y)//���´�ǽ���Ľڵ�������ϴ���
			for (i = 0; i < size; i++)
			{
				posBody = (PGAME_COORD)ListGetAt(snake_list, i);
				posHead->y = ListSize(snake_list) -1-i;
			}
	}
	
	/// �ж��Ƿ������Լ�
	//// �ӵڶ����ڵ㿪ʼ����һ��ͷ�ڵ�Ƚϡ�
	size = ListSize(snake_list);////��ȡ�������ĳ���  zbj

	for (i = 1; i < size; i++)
	{
		posBody = (PGAME_COORD)ListGetAt(snake_list, i);//ȡ�������ĵ�i���ڵ��λ��ָ��   zbj
		if (CoordEqual(posHead, posBody))//�����ײ�ĺ���   //����κ�һ���ڵ���ͷ�ڵ㷢����ײ�൱���������Լ�   zbj
		{
			return SNAKE_DEAD;//��������   zbj
		}
	}
	//�Ƿ�Ե���ҩ
	for (i = 0; i < 18; i++)
	{
		if (CoordEqual(posHead, drug[i]))//��ͷ�Ƿ���ʳ�﷢����ײ      zbj
		{
			return SNAKE_DEAD;//��������   zbj

		}
	}

	return SNAKE_MOVED;//�������������û�������߿��������ƶ� zbj
}

// �����ߣ��ͷ��ڴ���Դ��
void DistroySnake()
{
	ListDistoryAndFree(snake_list);
	return;
}

// �����ƶ�һ����
// �ƶ��Ժ�����Ե���ʳ���������
// ���������ǽ�����Լ������������������Ƿ�������״̬��
int SnakeMove()
{
	// ͷ��β������
	PGAME_COORD posHead;
	PGAME_COORD posTail;

	// ��β��������ȡ�������յ�ǰ������õ�ͷ��λ�á�
	posHead = (PGAME_COORD)ListGetAt(snake_list, 0);//���������ͷ�ڵ��λ��  zbj
	posTail = (PGAME_COORD)ListPopBack(snake_list);

	// ���ݵ�ǰ�������趨�µ�ͷ���ꡣ
	switch (snake_dir)
	{//
	case SNAKE_UP://������ϣ�ͷ�ڵ�λ������     zbj
		posTail->y = posHead->y - 1;
		posTail->x = posHead->x;
		break;
	case SNAKE_DOWN://������£�ͷ�ڵ�λ������   zbj
		posTail->y = posHead->y + 1;
		posTail->x = posHead->x;
		break;
	case SNAKE_LEFT://�������ͷ�ڵ�λ������   zbj
		posTail->x = posHead->x - 1;
		posTail->y = posHead->y;
		break;
	case SNAKE_RIGHT://������ң�ͷ�ڵ�λ������   zbj
		posTail->x = posHead->x + 1;
		posTail->y = posHead->y;
		break;
	}
	ListPushFront(snake_list, posTail);//���������µ�ͷ���ڵ��data����ͷλ�ã��ӵ���ͷ   zbj

	// �ж��Ƿ�Ե���ʳ��
	if (CoordEqual(posHead, food[0])|| CoordEqual(posHead, food[1]))//��ͷ�Ƿ���ʳ�﷢����ײ      zbj
	{
		return SNAKE_EATEN_FOOD;//�����˺�
	}

	// ���û�гԵ�ʳ���ж��Ƿ�ײ���ϰ���Ȼ�󷵻�״̬��
	return IsSnakeDead();
}

// ������
int SnakeGorwup()//���ߵ�β��׷��һ���ڵ�
{
	// ���µĽڵ�����ڴ�
	PGAME_COORD pNewTail;//��������ָ�룬�����½ڵ��ָ��   
	PGAME_COORD pTail;		// ������һ�ڵ�  
	PGAME_COORD pLastButOne;	// �����ڶ��ڵ�    
	int size = GetSnakeSize();//��ȡ�ߵĳ��� zbj

	if (size >= boundary.x*boundary.y - 1) //������ˣ���Ϸ������~//�ߵĳ��ȳ����˱߽������޶� zbj
		return SNAKE_COMPLETE;//������Ϸ���

	if (size == 0) // û��ͷ����֪�Ӻ����������ش���
		return SNAKE_ERROR;
	//�����µ���β��

	pNewTail = (PGAME_COORD)malloc(sizeof(GAME_COORD));//�����ڴ棬���ڴ�浽ָ��
	if (size == 1) // ֻ��һ���ڵ㣬���յ�ǰ���ƶ�����������
	{

		pTail = (PGAME_COORD)GetSnakeTail();//�����½ڵ��λ�ã���Ҫ�ѵ�����һ���ڵ��λ���õ�
		switch (snake_dir)
		{
		case SNAKE_LEFT://���������������Ļ����ұ� zbj
			pNewTail->x = pTail->x + 1;
			pNewTail->y = pTail->y;
			break;
		case SNAKE_RIGHT://���������ң������Ļ������ zbj
			pNewTail->x = pTail->x - 1;
			pNewTail->y = pTail->y;
			break;
		case SNAKE_UP://���������ϣ������Ļ����±�  zbj
			pNewTail->x = pTail->x;
			pNewTail->y = pTail->y + 1;
			break;
		case SNAKE_DOWN://���������£������Ļ����ϱ�  zbj
			pNewTail->x = pTail->x;
			pNewTail->y = pTail->y - 1;
			break;
		}

	}
	else // ���������Ͻڵ㣬ȡ������һ�͵����ڶ�������������
	{
		pTail = (PGAME_COORD)GetSnakeTail();//ȡ���������һ���ڵ��λ��ָ��  zbj
		pLastButOne = (PGAME_COORD)GetSnakeAt(size - 2);//ȡ�����������ڶ����ڵ��λ��ָ��  zbj 
		// ���ŵ����ڶ�->������һ�ķ�������һ���µĽڵ㡣
		pNewTail->x = pTail->x + (pTail->x - pLastButOne->x);//�������⻭ͼ��֪ zbj
		pNewTail->y = pTail->y + (pTail->y - pLastButOne->y);

	}//ǰ�涼����λ��  zbj

	// �½ڵ���뵽��β��λ��
	ListPushBack(snake_list, pNewTail);//�����ݷ�������β   zbjk
	return SNAKE_GROWUP;//��־�������ɹ�  zbj

}

// ����ߵĳ���
int GetSnakeSize()
{
	return ListSize(snake_list);//�����������ĳ��ȴ�С
}

// ����ߵĵ�һ���ڵ������
PGAME_COORD GetSnakeHead()
{
	return (PGAME_COORD)ListGetAt(snake_list, 0);
}

// ����ߵ����һ���ڵ������
PGAME_COORD GetSnakeTail()
{
	return (PGAME_COORD)ListGetAt(snake_list, GetSnakeSize() - 1);//��ָ�����ʽ�������������һ���ڵ㷵�� zbj
}

// ������Ż���ߵĽڵ�����꣬���ܳ����ߵĳ��ȣ����򷵻�NULL
PGAME_COORD GetSnakeAt(int n)//��������� zbj
{
	if (n < ListSize(snake_list))//����Ų������ߵĳ���ʱ zbj
		return (PGAME_COORD)ListGetAt(snake_list, n);//��ָ�����ʽ������������ָ���ڵ�
	else
		return NULL;

}

// �ı����ƶ��ķ���
void SetDirction(dirction dir)
{
	//����ԭ�ص�ͷ����ɱ�����൱�ڰ���Ҳ�װ�
	switch (snake_dir)//������̶��ߵ��ƶ����������ߵ�ǰ���ƶ������෴�ģ���ô��return NULL�����ı��ߵ��ƶ����������������������ͽ��ߵķ����Ϊ���������ݵķ��� zbj
	{
	case SNAKE_UP:
		if (dir == SNAKE_DOWN)
			return;
		break;
	case SNAKE_DOWN:
		if (dir == SNAKE_UP)
			return;
		break;
	case SNAKE_LEFT:
		if (dir == SNAKE_RIGHT)
			return;
		break;
	case SNAKE_RIGHT:
		if (dir == SNAKE_LEFT)
			return;
		break;
	}
	snake_dir = dir;//�ı�ȫ�ֱ����ߵķ���   zbj//��ֵ��ȫ�ֱ���   zbjk
}


// ��õ�ǰ�ߵķ���
dirction GetDirction()
{
	return snake_dir;//����ȫ�ֱ���
}