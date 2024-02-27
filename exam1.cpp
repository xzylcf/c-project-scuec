#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_VERTICES 10
#define MAX_EDGES 25
#define MAX_DELIVERIES 100

typedef struct
{
    char name[MAX_NAME_LENGTH];
    int type;          // 0代表仓库，1代表客户点
    int totalOutbound; // 当日寄件数量
    int totalInbound;  // 当日收件数量
} Vertex;

typedef struct
{
    int source;      // 起点
    int destination; // 终点
    int weight;      // 路径长度
} Edge;

typedef struct
{
    char customerPoint[MAX_NAME_LENGTH]; // 客户点
    int type;                            // 0代表寄件，1代表收件
    char recipientName[MAX_NAME_LENGTH]; // 收件人姓名
    char phone[MAX_NAME_LENGTH];
    int delivered; // 投递状态，0代表未投递，1代表已投递,2代表配送中，3代表已送达
    char info[MAX_NAME_LENGTH]; // 快递的详细信息，如分类等等
} Delivery;

typedef struct
{
    Vertex vertices[MAX_VERTICES];
    Edge edges[MAX_EDGES];
    Delivery deliveries[MAX_DELIVERIES];
    int numVertices;
    int numEdges;
    int numDeliveries;
} Graph;

void initializeGraph(Graph *graph)
{
    graph->numVertices = 0;
    graph->numEdges = 0;
    graph->numDeliveries = 0;
}

void addVertex(Graph *graph, char name[], int type, int totalOutbound, int totalInbound)
{
    if (graph->numVertices >= MAX_VERTICES)
    {
        printf("达到节点的最大数量，error！\n");
        return;
    }

    Vertex newVertex;
    strcpy(newVertex.name, name);
    newVertex.type = type;
    newVertex.totalOutbound = totalOutbound;
    newVertex.totalInbound = totalInbound;

    graph->vertices[graph->numVertices] = newVertex;
    graph->numVertices++;
}

void addEdge(Graph *graph, int source, int destination, int weight)
{
    if (graph->numEdges >= MAX_EDGES)
    {
        printf("达到边的最大数量，error！\n");
        return;
    }

    Edge newEdge;
    newEdge.source = source;
    newEdge.destination = destination;
    newEdge.weight = weight;

    graph->edges[graph->numEdges] = newEdge;
    graph->numEdges++;
}

void addDelivery(Graph *graph, char customerPoint[], int type, char recipientName[], char phone[], int delivered,char info[])
{
    if (graph->numDeliveries >= MAX_DELIVERIES)
    {
        printf("达到快递的最大数量，error！\n");
        return;
    }

    Delivery newDelivery;
    strcpy(newDelivery.customerPoint, customerPoint);
    newDelivery.type = type;
    strcpy(newDelivery.recipientName, recipientName);
    strcpy(newDelivery.phone, phone);
    newDelivery.delivered = delivered;
    strcpy(newDelivery.info, info);

    graph->deliveries[graph->numDeliveries] = newDelivery;
    graph->numDeliveries++;
}

void displayVertices(Graph *graph)
{
    printf("节点:\n");
    for (int i = 0; i < graph->numVertices; i++)
    {
        printf("%s (Type: %d, Outbound: %d, Inbound: %d)\n",
               graph->vertices[i].name, graph->vertices[i].type,
               graph->vertices[i].totalOutbound, graph->vertices[i].totalInbound);
    }
    printf("\n");
}

void displayEdges(Graph *graph)
{
    printf("边:\n");
    for (int i = 0; i < graph->numEdges; i++)
    {
        printf("%s <-> %s (Weight: %d)\n", graph->vertices[graph->edges[i].source].name,
               graph->vertices[graph->edges[i].destination].name, graph->edges[i].weight);
    }
    printf("\n");
}

void displayDeliveries(Graph *graph)
{
    printf("快递信息:\n");
    for (int i = 0; i < graph->numDeliveries; i++)
    {
        printf("%s (%s) - %s (%s), Delivered: %d,info:%s\n", graph->deliveries[i].customerPoint,
               graph->deliveries[i].type == 0 ? "寄件" : "收件", graph->deliveries[i].recipientName,
               graph->deliveries[i].phone, graph->deliveries[i].delivered,graph->deliveries[i].info);
    }
    printf("\n");
}

void saveGraphToFile(Graph *graph, char filename[])
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file！\n");
        return;
    }

    // Save vertices
    fprintf(file, "%d\n", graph->numVertices);
    for (int i = 0; i < graph->numVertices; i++)
    {
        fprintf(file, "%s %d %d %d\n", graph->vertices[i].name, graph->vertices[i].type,
                graph->vertices[i].totalOutbound, graph->vertices[i].totalInbound);
    }

    // Save edges
    fprintf(file, "%d\n", graph->numEdges);
    for (int i = 0; i < graph->numEdges; i++)
    {
        fprintf(file, "%d %d %d\n", graph->edges[i].source, graph->edges[i].destination, graph->edges[i].weight);
    }

    // Save deliveries
    fprintf(file, "%d\n", graph->numDeliveries);
    for (int i = 0; i < graph->numDeliveries; i++)
    {
        fprintf(file, "%s %d %s %s %d %s\n", graph->deliveries[i].customerPoint,
                graph->deliveries[i].type, graph->deliveries[i].recipientName, graph->deliveries[i].phone,
                graph->deliveries[i].delivered,graph->deliveries[i].info);
    }

    fclose(file);
}

void loadGraphFromFile(Graph *graph, char filename[])
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file！\n");
        return;
    }

    // Load vertices
    fscanf(file, "%d", &graph->numVertices);
    for (int i = 0; i < graph->numVertices; i++)
    {
        fscanf(file, "%s %d %d %d", graph->vertices[i].name, &graph->vertices[i].type,
               &graph->vertices[i].totalOutbound, &graph->vertices[i].totalInbound);
    }

    // Load edges
    fscanf(file, "%d", &graph->numEdges);
    for (int i = 0; i < graph->numEdges; i++)
    {
        fscanf(file, "%d %d %d", &graph->edges[i].source, &graph->edges[i].destination, &graph->edges[i].weight);
    }

    // Load deliveries
    fscanf(file, "%d", &graph->numDeliveries);
    for (int i = 0; i < graph->numDeliveries; i++)
    {
        fscanf(file, "%s %d %s %s %d %s", graph->deliveries[i].customerPoint, &graph->deliveries[i].type,
               graph->deliveries[i].recipientName, graph->deliveries[i].phone, &graph->deliveries[i].delivered, graph->deliveries[i].info);
    }

    fclose(file);
}

void editDelivery(Graph *graph)
{
    char customerPoint[MAX_NAME_LENGTH];
    int type;
    char recipientName[MAX_NAME_LENGTH];
    char phone[MAX_NAME_LENGTH];
    char info[MAX_NAME_LENGTH];

    printf("输入快递信息:\n");
    printf("客户点名称: \n");
    scanf("%s", customerPoint);
    printf("类型 (0 for 寄件, 1 for 收件): \n");
    scanf("%d", &type);
    printf("收/寄件人姓名: \n");
    scanf("%s", recipientName);
    printf("电话: \n");
    scanf("%s", phone);
    printf("快递详细信息:\n");
    scanf("%s",info);

    // 查找对应的快递信息
    for (int i = 0; i < graph->numDeliveries; i++)
    {
        if (strcmp(graph->deliveries[i].customerPoint, customerPoint) == 0 &&
            graph->deliveries[i].type == type &&
            strcmp(graph->deliveries[i].recipientName, recipientName) == 0 &&
            strcmp(graph->deliveries[i].phone, phone) == 0 &&
            strcmp(graph->deliveries[i].info, info) == 0)
        {

            // 更新送达状态
            printf("修改状态，0：未投递，1：已投递，2：配送中，3：已送达");
            int t;
            scanf("%d",&t);
            graph->deliveries[i].delivered = t;
            printf("快递状态已更新。\n");
            return;
        }
    }

    printf("快递信息未找到.\n");
}

void findDeliveriesByCustomerPoint(Graph *graph)
{
    char customerPoint[MAX_NAME_LENGTH];
    printf("输入客户点名称: ");
    scanf("%s", customerPoint);
    printf("属于该点的快递信息 '%s':\n", customerPoint);

    for (int i = 0; i < graph->numDeliveries; i++)
    {
        if (graph->deliveries[i].customerPoint[0] == customerPoint[0])
        {
            printf("%s (%s) - %s (%s), Delivered: %s, info: %s\n", graph->deliveries[i].customerPoint,
                   graph->deliveries[i].type == 0 ? "Outbound" : "Inbound", graph->deliveries[i].recipientName,
                   graph->deliveries[i].phone, graph->deliveries[i].delivered ? "Yes" : "No",
                   graph->deliveries[i].info);
        }
    }
}

void findDeliveryByPhone(Graph *graph, const char phone[])
{
    printf("属于该电话的快递信息： '%s':\n", phone);

    for (int i = 0; i < graph->numDeliveries; i++)
    {
        if (strcmp(graph->deliveries[i].phone, phone) == 0)
        {
            printf("%s (%s) - %s (%s), Delivered: %s,info: %s\n", graph->deliveries[i].customerPoint,
                   graph->deliveries[i].type == 0 ? "Outbound" : "Inbound", graph->deliveries[i].recipientName,
                   graph->deliveries[i].phone, graph->deliveries[i].delivered ? "Yes" : "No",
                   graph->deliveries[i].info);
            
        }
        if(i == graph->numDeliveries-1){
            return ;
        }
    }

    printf("没有找到对应电话的快递信息 '%s'.\n", phone);
}

void findDeliveriesByType(Graph *graph)
{
    int type;
    printf("输入想查询的类型（0寄件/1收件）: ");
    scanf("%d", &type);
    printf("属于该类型的快递信息 '%s':\n", type==0?"寄件":"收件");

    for (int i = 0; i < graph->numDeliveries; i++)
    {
        if (graph->deliveries[i].type == type)
        {
            printf("%s (%s) - %s (%s), Delivered: %s, info: %s\n", graph->deliveries[i].customerPoint,
                   graph->deliveries[i].type == 0 ? "Outbound" : "Inbound", graph->deliveries[i].recipientName,
                   graph->deliveries[i].phone, graph->deliveries[i].delivered ? "Yes" : "No",
                   graph->deliveries[i].info);
        }
    }
}

#define INF 9999

void dijkstra(Graph *graph, int start, int end)
{
    int distance[MAX_VERTICES];
    int visited[MAX_VERTICES];
    int prev[MAX_VERTICES];

    for (int i = 0; i < graph->numVertices; i++)
    {
        distance[i] = INF;
        visited[i] = 0;
        prev[i] = -1;
    }
    distance[start] = 0;

    for (int i = 0; i < graph->numVertices - 1; i++)
    {
        int u = -1;
        int minDistance = INF;
        for (int j = 0; j < graph->numVertices; j++)
        {
            if (!visited[j] && distance[j] < minDistance)
            {
                u = j;
                minDistance = distance[j];
            }
        }

        if (u == -1 || u == end)
        {
            break;
        }

        visited[u] = 1;

        for (int v = 0; v < graph->numEdges; v++)
        {
            if (graph->edges[v].source == u)
            {
                int node = graph->edges[v].destination;
                int weight = graph->edges[v].weight;
                if (!visited[node] && distance[u] != INF &&
                    distance[u] + weight < distance[node])
                {
                    distance[node] = distance[u] + weight;
                    prev[node] = u;
                }
            }
        }
    }

    printf("最短路径从 %d 到 %d: %d\n", start, end, distance[end]);

    // 输出最短路径的节点名称
    printf("最短路径: ");
    int current = end;
    while (current != -1)
    {
        printf("%s ", graph->vertices[current].name);
        current = prev[current];
    }
    printf("\n");
}

// 显示主菜单
void displayMainMenu()
{
    printf("========== 快递配送系统 ==========\n");
    printf("1. 增加顶点/边/快递信息\n");
    printf("2. 显示图的信息(图片)\n");
    printf("3. 显示顶点/边/快递信息\n");
    printf("4. 修改快递信息\n");
    printf("5. 按照客户点名称查询快递信息\n");
    printf("6. 按照收件人电话查询快递信息\n");
    printf("7. 按照快递类型查询快递信息\n");
    printf("8. 查询最优配送路径\n");
    printf("9. 保存图至文件中\n");
    printf("0. 退出系统\n");
    printf("==================================\n");
    printf("请输入选项：");
}

void shuru(Graph &graph);

void admin(Graph &graph);

void user(Graph &graph);
void courier(Graph &graph);

int main()
{
    // 初始化
    Graph graph;
    initializeGraph(&graph);

    int menuChoose;
    do
    {
        printf("本系统有3个页面，1：管理员界面，2：用户界面,3:快递员界面\n请输入你想进入的界面:");
        scanf("%d", &menuChoose);
        if (menuChoose == 1)
        {
            admin(graph);
        }
        else if (menuChoose == 2)
        {
            user(graph);
        }else if(menuChoose == 3){
            courier(graph);
        }
        else
            printf("输入的选项有误！");
        printf("输入0即可退出系统,输入1继续:");
        scanf("%d", &menuChoose);
    } while (menuChoose != 0);

 printf("谢谢使用！");
    return 0;
}
// 显示快递员菜单
void displayCourierMenu()
{
    printf("========== 快递配送系统(快递员) ==========\n");
    printf("1. 显示快递信息\n");
    printf("2. 修改快递信息(是否配送)\n");
    printf("3. 查询快递信息(客户点名称)\n");
    printf("4. 查询快递信息(电话)\n");
    printf("5. 查询最优配送路径\n");
    printf("0. 退出系统\n");
    printf("==================================\n");
    printf("请输入选项：");
}

void courier(Graph &graph)
{
int option;
    do
    {
        displayCourierMenu();
        scanf("%d", &option);
        switch (option)
        {
        case 1:
        {
            displayDeliveries(&graph);
        }
        break;
        case 2:
        {
            editDelivery(&graph);
        }
        break;
        case 3:
        {
             findDeliveriesByCustomerPoint(&graph);
        }
        break;
        case 4:{
            char phone[15];
            printf("请输入想查询的电话号码:");
            scanf("%s", phone);
            findDeliveryByPhone(&graph, phone);
        }
            
            break;
        case 5:
        {
            int start, end;
            printf("请输入你想查询的两点：\n");
            scanf("%d %d", &start, &end);
            dijkstra(&graph, start, end);
        }
        break;
        
        case 0:
            printf("退出系统。\n");
            break;
        default:
            printf("无效选项，请重新输入。\n");
            break;
        }
    } while (option != 0);
}
void user(Graph &graph)
{
    printf("欢迎您的使用^_^\n");
    char phone[15] ;
    printf("请输入你的号码（查询快递状态）:");
    scanf("%s",phone);
    findDeliveryByPhone(&graph,phone);
    
}
void admin(Graph &graph)
{
    int option;
    do
    {
        displayMainMenu();
        scanf("%d", &option);

        switch (option)
        {
        case 1:
        {
            shuru(graph);
        }
        break;
        case 2:
        {
            system("mspaint graph.png");
        }
        break;
        case 3:
        {
            displayVertices(&graph);
            displayEdges(&graph);
            displayDeliveries(&graph);
        }
        break;
        case 4:
            editDelivery(&graph);
            break;
        case 5:
        {
            findDeliveriesByCustomerPoint(&graph);
        }
        break;
        case 6:
        {
            char phone[15];
            printf("请输入想查询的电话号码:");
            scanf("%s", phone);
            findDeliveryByPhone(&graph, phone);
        }
        break;
        case 7:
        {
            findDeliveriesByType(&graph);
        }
        break;
        case 8:
        {
            int start, end;
            printf("请输入你想查询的两点：\n");
            scanf("%d %d", &start, &end);
            dijkstra(&graph, start, end);
        }
        break;
        case 9:
        {
            saveGraphToFile(&graph, "save_file");
            printf("已保存图至文件中\n");
        }
        break;
        case 0:
            printf("退出系统。\n");
            break;
        default:
            printf("无效选项，请重新输入。\n");
            break;
        }
    } while (option != 0);
}

void shuru(Graph &graph)
{
    int s = 0;
    printf("文件读取：1\t自己输入：2\n");
    scanf("%d", &s);

    if (s == 1)
    {
        loadGraphFromFile(&graph, "graph_data.txt");
    }
    else if (s == 2)
    {
        int t = 0, num = 0;
        printf("输入你想添加的信息 -   节点：0\t边：1\t快递信息：2\n");
        scanf("%d", &t);
        printf("输入你想添加信息的条数\n");
        scanf("%d", &num);
        if (t == 2)
        {
            for (int i = 0; i < num; i++)
            {
                char s1[MAX_NAME_LENGTH];
                int s2 = 0;
                char s3[MAX_NAME_LENGTH];
                char s4[MAX_NAME_LENGTH];
                int s5;
                char s6[MAX_NAME_LENGTH];
                printf("这是输入的快递信息格式：客户点名称 数字（0代表寄件，1代表收件） 收/寄件人姓名 电话 （投递状态，0代表未投递，1代表已投递，2代表配送中，3代表已送达） 详细信息\n");
                scanf("%s %d %s %s %d %s", s1, &s2, s3, s4, &s5,s6);
                addDelivery(&graph, s1, s2, s3, s4, s5,s6);
            }
        }
        else if (t == 0)
        {
            for (int i = 0; i < num; i++)
            {
                char s1[MAX_NAME_LENGTH];
                int s2 = 0;
                int s3 = 0;
                int s4 = 0;
                printf("这是输入的节点格式：客户点名称 数字（0代表仓库，1代表客户点） 当日寄件数量 当日收件数量\n");
                scanf("%s %d %d %d", s1, &s2, &s3, &s4);
                addVertex(&graph, s1, s2, s3, s4);
            }
        }
        else if (t == 1)
        {
            for (int i = 0; i < num; i++)
            {
                int s1 = 0;
                int s2 = 0;
                int s3 = 0;
                printf("这是输入的边格式：起点 终点 路径长度\n");
                scanf("%d %d %d", &s1, &s2, &s3);
                addEdge(&graph, s1, s2, s3);
            }
        }
        else
        {
            printf("输入的信息类型有误！");
        }
    }
    else
    {
        printf("输入方式有误！");
    }
}
