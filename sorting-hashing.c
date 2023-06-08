/*
 * sorting-hashing.c
 *
 *  Sorting & Hashing
 * 
 * 자료구조 11번째 과제 
 * 충북대학교 2017015040 물리학과 강수
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	//배열 최대크기 (소수)
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE//해쉬 테이블 크기

int initialize(int **a);//초기화
int freeArray(int *a);//메모리해지
void printArray(int *a);//배열출력

int selectionSort(int *a);//선택정렬
int insertionSort(int *a);//삽입정렬
int bubbleSort(int *a);//버블정렬
int shellSort(int *a);//쉘정영
int quickSort(int *a, int n);//재귀형태의 퀵정렬

int hashCode(int key);//나머지를 이용해 해쉬코드를 생성

int hashing(int *a, int **ht);//배열 a에 대한 해쉬테이블을 만든다


int search(int *ht, int key);//해쉬 테이블에서 키를 찾아 해쉬테이블의 인덱스를 리턴한다.


int main()
{
	char command;//구별자
	int *array = NULL;//배열
	int *hashtable = NULL;//해쉬테이블
	int key = -1;//찾을 키값
	int index = -1;//해쉬 테이블 저장위치

	srand(time(NULL));//난수 생성값 설정
	printf("[-------------------- [kang su] [2017015040] -------------------]\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);//배열의 주소전달
			break;
		case 'q': case 'Q':
			freeArray(array);//값전달
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);//키값이 위치한 인덱스 반환
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

    //배열이 메모리 할당이 되지 않은 경우
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);//배열 최대수 만큼 int형 메모리할당
		*a = temp; //할당된 메모리 주소로 포인터를 변경
	} else//메모리가 있을경우
		temp = *a;//할당된 이미 메모리주소를 받아온다

	//랜덤값으로 배정
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;//난수를 받아오고 배열 최대 크기로 나눔

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL)//배열이 NULL이 아니면
		free(a);//배열을 초기화한다
	return 0;
}

void printArray(int *a)//배열출력
{
	if (a == NULL) {//배열이 없으면
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a)//선택정렬
{
	int min;//최소값 백업,값 교체시 필요
	int minindex;//최소 인덱스 위치 등록에 사용
	int i, j;//비교 인덱스 위치

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);//정렬전 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++)//처음부터 끝까지
	{
		minindex = i;//최소 인덱스 위치
		min = a[i];//최소값으로 설정
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)//최소 인덱스의 오른쪽을 탐색
		{
			if (min > a[j])//j번째 값이 치소값보다 작으면
			{
				min = a[j];//최소값으로 j번째 값을 등록
				minindex = j;//최소값 위치 갱신
			}
		}
        //최소인 덱스와 이전 최소 인덱스를 교체
		a[minindex] = a[i];
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);//정렬후 출력
	return 0;
}

int insertionSort(int *a)//삽입정렬
{
	int i, j, t;//(i,j)는 배열 위치, t는 배열 값

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);//정렬전 배열 출력

	for(i = 1; i < MAX_ARRAY_SIZE; i++)//전배열 탐색
	{
		t = a[i];//초기 기준값
		j = i;//기준 위치
		while (a[j-1] > t && j > 0) //기준 왼쪽 값이 기준 값보다 큰경우 그리고 기준값이 0보다 큰 경우
		{
			a[j] = a[j-1];//기준 값에 기준 왼쪽 값을 저장, 왼쪽 기준값이 오른쪽으로 이동한 효과
            //영역내에서 작은 값은 왼쪽으로 큰값은 오른쪽으로 이동한다
			j--;//기준을 왼쪽으로 이동
		}
		a[j] = t;//가장 왼쪽의 값에 초기 기준값을 저장
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);//정렬후 배열출력

	return 0;
}

int bubbleSort(int *a)//버블정렬
{
	int i, j, t;//(i,j)는 배열 위치, t는 배열 값

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);//정렬 전 출력

	for(i = 0; i < MAX_ARRAY_SIZE; i++)//전범위 탐색
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)//j~끝까지 탐색
		{
			if (a[j-1] > a[j])//기준값보다 왼족값이 큰경우
			{
				t = a[j-1];//왼족 값 백업
				a[j-1] = a[j];//기준값을 왼쪽 값에 저장
				a[j] = t;//기준값에 백업된 왼쪽 값 저장
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);//정렬후출력

	return 0;
}

int shellSort(int *a)//셀정렬
{
	int i, j, k, h, v;//i와 j는 위치, h는 비교할 위치 간 거리 단위, v는 값 ,k는 비교 위치

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)//비교거리 초기화는 전체의 절반, 비교거리 0보다 클때까지, 비교거리 크기를 절반으로
	{
		for (i = 0; i < h; i++)//0부터 h이전 탐색
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)//j는 i위치+절반, j가 h(비교 거리)보다 작을 때까지, j를 h(비교거리)만큼 증가
			{
				v = a[j];//j위치 값 백업
				k = j;//j위치 백업
				while (k > h-1 && a[k-h] > v)//k위치가 h(비교 거리) 이상이고 그리고 k에서 h(비교 거리)을 뺀 값이 j위치 값 보다 큰경우
				{
					a[k] = a[k-h];//비교 대상중 왼쪽값을 오른쪽에 덮어씌운다
					k -= h;//k에서 h을 뺀다
				}
				a[k] = v;//비교대상에서 오른쪽값을 왼쪽에 덮어 씌운다
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n)//퀵 정렬 (생성된 배열 포인터 ,배열 최대크기)
{
	int v, t;//값 v는 비교 기준 ,t는 백업용
	int i, j;//위치

	if (n > 1)
	{
		v = a[n-1];//마지막 배열, 비교 기준
		//초기화
        i = -1;
		j = n - 1;

		while(1)
		{
			while(a[++i] < v);//i위치 초기화 = 처음부터, 마지막 값보다 i위치의 값이 작을 때까지 오른쪽으로 이동
			while(a[--j] > v);//j위치 초기화 = 마지막 전부터, 마지막 값보다 j위치의 값이 클때까지 왼쪽으로 이동

			if (i >= j) break;//i가 j보다 크거나 같을 경우, 비교 위치 교차시 정지
            //왼쪽(i)과 오른쪽(j) 교체
			t = a[i];//왼쪽 값 백업
			a[i] = a[j];//왼쪽 값에 오른쪽 값을 대입
			a[j] = t;//오른쪽 값에 왼쪽 값 대입
		}
		t = a[i];//i j 교차점값 백업 
		a[i] = a[n-1];//비교 값을 해당 위치에 교차점 값 대입 
		a[n-1] = t;//마지막 위치에 교차점 백업값을 대입

		quickSort(a, i);//가운데 기준 왼쪽 정렬 시작
		quickSort(a+i+1, n-i-1);//가운대 기준 오른쪽 정렬
	}


	return 0;
}

int hashCode(int key) {//해쉬코드 변환 함수
   return key % MAX_HASH_TABLE_SIZE;//받아온 값을 최대크기로 나눴을때의 나머지를 반환 
}

int hashing(int *a, int **ht)//해쉬 할당
{
	int *hashtable = NULL;//해쉬 테이블 포인터

    //해쉬테이블이 널인 경우에 메모리 할당
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  //할당된 주소를 복사 매인에서 사용가능
	} else {
		hashtable = *ht;//해쉬 테이블이 이미 있을경우 기존해쉬 테이블 재사용 
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;//모든 값을 -1로 리셋

	int key = -1;//키값
	int hashcode = -1;//저장위치를 정하는데 참고
	int index = -1;//해쉬코드위치에 무언가 있을 경우 사용
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)//전범위 탐색
	{
		key = a[i];//값을 받아와
		hashcode = hashCode(key);//해쉬코드로 돌린다

		if (hashtable[hashcode] == -1)//해당 위치가 값이 초기값인경우
		{
			hashtable[hashcode] = key;//그 자리에 값을 집어 넣는다 
		} else 	{//아닌경우

			index = hashcode;//해쉬코드 위치를 받아온다

			while(hashtable[index] != -1)//사용중인 자리가 아닌경우
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;//최대범위 내에서 값을 증가시키며 들어갈 빈자리를 찾는다 
			}
			hashtable[index] = key;//값저장
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);//해쉬를 돌려 키값을 받는다

	if(ht[index] == key)//해당위치에 값이 있는지 찾는다 있으면 값 반환
		return index;

    //값이 배열안에 없을 경우 무한루프를 돈다
	while(ht[++index] != key)//없을 경우 값을 찾을 때까지 한칸씩 이동한다
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}


