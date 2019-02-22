//#include "iostream"
//#include "list"
//#include "vector"
//#include "fstream"
//using namespace std;
//class DataNode;
//class Edge{
//public:
//    string a;
//    string b;
//    string *match,*depend;
//    int setEdge(){
//        cin >> a >> b;
//    }
//    bool operator ==(string dataName){
//        if(a==dataName){
//            match=&a;
//            depend=&b;
//            return 1;
//        }else if(b==dataName){
//            match=&b;
//            depend=&a;
//            return 1;
//        }
//        return 0;
//    }
////    bool operator ==(DataNode x);
//};
//class DataNode{
//public:
//    string dataName;
//    int dataContent;
//    bool flag;
//    list <int> edgeList;
//    DataNode(){
//        dataName= "";
//        dataContent=0;
//        flag=0;
//    }
//    int setDataNodes(string name, int content){
//        dataName=name;
//        dataContent=content;
//    }
//    void clearFlag(){
//        flag=0;
//    }
//    bool operator ==(Edge *x ){
//        if(x->a==dataName){
//            x->match=&(x->a);
//            x->depend=&(x->b);
//            return 1;
//        }else if(x->b==dataName){
//            x->match=&(x->b);
//            x->depend=&(x->a);
//            return 1;
//        }
//        return 0;
//    }
//    bool operator ==(string x){
//        if(dataName==x)
//            return 1;
//        else
//            return 0;
//    }
//    bool operator ==(DataNode x){
//        if(x.dataName==dataName&&x.dataContent==dataContent)
//            return 1;
//        else
//            return 0;
//
//    }
//};
//class Graph{
//public:
//    string name;
//    vector <DataNode> data;
//    bool operator ==(const string &x){
//        if(x==name)
//            return 1;
//        else
//            return 0;
//    }
//};
//class DataSet{
//public:
//    vector <DataNode> data;
//    int setDataSet(){
//        int size;
//        cin >> size;
//        for(int i=0;i<size;i++){
//            string name;
//            int content;
//            cin >> content >> name;
//            data.emplace(data.end()).base()->setDataNodes(name,content);
//        }
//    }
//};
//class EdgeSet{
//public:
//    vector <Edge> data;
//    int setEdgeSet(){
//        int size=0;
//        cin >> size;
//        for(int i=0;i<size;i++){
//            data.emplace(data.end()).base()->setEdge();
//        }
//    }
//};
//bool compare(){
//
//}
//typedef int (*Visit)(DataNode &x);
//class Index{
//public:
//    vector <Graph> graphs;
//    int CreateGraph(string name, DataSet originData, EdgeSet originEdge);
////    int EdgeRelateNode(string name,Edge a,DataNode b){
////        auto target=find(graphs.begin(),graphs.end(),name);
////        if(target!=graphs.end()){
////            //find target
////            auto match=find(target.base()->data.begin(),target.base()->data.end(),)
////        }
////    }
//    int getSequence(string name,string nodeName);
//    int DestroyGraph(string name);
//    int LocateVex(string name, DataNode u);
//    int GetVex(string name, string v);
//    int PutVex(string name ,DataNode u,int newValue);
//    DataNode FirstAdjVex(string name, DataNode v);
//    DataNode NextAdjVex(string name ,DataNode v,DataNode u);
//    int InsertVex(string name, DataNode v);
//    int DeleteVex(string name, DataNode v);
//    int InsertArc(string name, DataNode v, DataNode w);
//    int DeleteArc(string name, DataNode v, DataNode w);
//    function<int(DataNode&)> visitFunc;
//    int DFSTraverse(string name,Visit visit);
//    int DFSStep(DataNode &x, vector <DataNode> &targetData);
//    int BFSTraverse(string name,Visit visit);
//    int BFSStep(DataNode &x, vector <DataNode> &targetData);
//    int Save();
//    int Load();
//};
//int Index::getSequence(string name, string nodeName) {
//    auto target=find(graphs.begin(),graphs.end(),name);
//    if(target!=graphs.end()){
//        //find target
//        auto &targetData=target.base()->data;
//        auto p=find(targetData.begin(),targetData.end(),nodeName);
//        if(p!=targetData.end())
//            return p-targetData.begin();
//    }
//    return -1;
//}
//int Index::CreateGraph(string name, DataSet origin, EdgeSet originEdge) {
//    if(find(graphs.begin(),graphs.end(),name)==graphs.end()){//no repeat
//        auto target=graphs.emplace(graphs.end()).base();
//        target->name=name;
//        target->data=origin.data;
//        //遍历所有节点，对于每个节点，寻找包含它的edge并加进去
//        for(DataNode &base:target->data){
//            auto match=find(originEdge.data.begin(),originEdge.data.end(),base.dataName);
//            //match是和Edge集源中和当前data节点名字相同的边，此时通过重载==已经把边的另一端的名字放到depend中
//            while (match != originEdge.data.end()){
//                //查找完所有元素
//                auto depend=find(target->data.begin(),target->data.end(),*(match.base()->depend))-target->data.begin();
//                //在所有data中寻找边的另一个点，并得出其次序
//                base.edgeList.push_back(depend);
//                match=find(match+1,originEdge.data.end(),base.dataName);
//                }
//            }
//        return 1;
//        }
//    return -1;
//};
//int Index::DestroyGraph(string name){
//    auto target=find(graphs.begin(),graphs.end(),name);
//    if(target!=graphs.end()){
//        //find target
//        graphs.erase(target);
//        return 1;
//    }
//    return -1;
//}
//int Index::LocateVex(string name,DataNode u){
//    auto target=find(graphs.begin(),graphs.end(),name);
//    if(target!=graphs.end()){
//        //find target
//        auto match=find(target.base()->data.begin(),target.base()->data.end(),u);
//        if(match!=target.base()->data.end()){
//            //match is the iterator of dataNode v in index
//            return match-target.base()->data.begin();
//        }
//    }
//    return -1;
//
//}
//int Index::GetVex(string name, string v) {
//    auto target=find(graphs.begin(),graphs.end(),name);
//    if(target!=graphs.end()){
//        //find target
//        auto match=find(target.base()->data.begin(),target.base()->data.end(),v);
//        if(match!=target.base()->data.end()){
//            //match
//            return match.base()->dataContent;
//        }
//
//    }
//    return -1;
//}
//int Index::PutVex(string name, DataNode u, int newValue){
//    auto target=find(graphs.begin(),graphs.end(),name);
//    if(target!=graphs.end()){
//        //find target
//        auto match=find(target.base()->data.begin(),target.base()->data.end(),u);
//        if(match!=target.base()->data.end()){
//            //match
//            match.base()->dataContent=newValue;
//            return 1;
//        }
//    }
//    return -1;
//}
//DataNode Index::FirstAdjVex(string name, DataNode v){
//    auto target=find(graphs.begin(),graphs.end(),name);
//    if(target!=graphs.end()){
//        //find target
//        auto match=find(target.base()->data.begin(),target.base()->data.end(),v);
//        if(match!=target.base()->data.end()&& match.base()->edgeList.size()!=0){
//            //match
//            return target.base()->data[match.base()->edgeList.front()];
//        }
//        else {
//            DataNode temp;
//            temp.dataName="";
//            temp.dataContent=-1;
//            return temp;
//        }
//    }
//    return {};
//}
//DataNode Index::NextAdjVex(string name, DataNode v, DataNode w){
//    auto target=find(graphs.begin(),graphs.end(),name);
//    if(target!=graphs.end()){
//        //find target
//        auto match=find(target.base()->data.begin(),target.base()->data.end(),v);
//        if(match!=target.base()->data.end()){
//            //match is the iterator of v
////            auto wMatch=find (match.base()->edgeList.begin(),match.base()->edgeList.end(),w);
//            //find w in v's edgelist
//            for(auto wMatch=match.base()->edgeList.begin();wMatch!=match.base()->edgeList.end();wMatch++){
//                if(target.base()->data[*wMatch]==w){
//                    wMatch++;
//                    if(wMatch==match.base()->edgeList.end()){
//                        DataNode temp;
//                        temp.dataName="";
//                        temp.dataContent=-1;
//                        return temp;
//                    }
//                    else{
//                        return target.base()->data[*wMatch];
//                    }
//                }
//
//            }
//        }
//        return {};
//    }
//}
//int Index::InsertVex(string name,DataNode v){
//    auto target=find(graphs.begin(),graphs.end(),name);
//    if(target!=graphs.end()){
//        //find target
//        auto match=find(target.base()->data.begin(),target.base()->data.end(),v.dataName);
//        if(match!=target.base()->data.end())
//            return -1;
//        target.base()->data.push_back(v);
//        return 1;
//    }
//    return -1;
//}
//int Index::DeleteVex(string name, DataNode v) {
//    auto target=find(graphs.begin(),graphs.end(),name);
//    if(target!=graphs.end()){
//        //find target
//        auto match=find(target.base()->data.begin(),target.base()->data.end(),v);
//        if(match!=target.base()->data.end()){
//            //match is the iterator of dataNode v in index
//            for(auto &eachNode:target.base()->data){
//                int num=match-target.base()->data.begin();
//                auto relateEdge=find(eachNode.edgeList.begin(),eachNode.edgeList.end(),num);
//                while(relateEdge!=eachNode.edgeList.end()){
//                    relateEdge=eachNode.edgeList.erase(relateEdge);
//                    relateEdge=find(eachNode.edgeList.begin(),eachNode.edgeList.end(),num);
//                }
//                for(auto &x:eachNode.edgeList){
//                    if(x>num)
//                        x--;
//                }
//            }
//            target.base()->data.erase(match);
//            return 1;
//        }
//
//    }
//    return -1;
//}
//int Index::InsertArc(string name,DataNode v,DataNode w){
//    auto target=find(graphs.begin(),graphs.end(),name);
//    if(target!=graphs.end()){
//        //find target
//        auto &targetData=target.base()->data;
//        auto numberW=find(targetData.begin(),targetData.end(),w);
//        auto numberV=find(targetData.begin(),targetData.end(),v);
//        if(numberV==targetData.end()||numberW==targetData.end())
//            return -1;
//        auto match=find(targetData.begin(),targetData.end(),v);
//        auto &matchEdge=match.base()->edgeList;
//        if(find(match.base()->edgeList.begin(),match.base()->edgeList.end(),numberW-targetData.begin())==match.base()->edgeList.end()){
//            //本来没有边w
//            match.base()->edgeList.push_back(numberW-targetData.begin());
//            match=find(targetData.begin(),targetData.end(),w);
//            match.base()->edgeList.push_back(numberV-targetData.begin());
//            return 1;
//        }
//
//        return -1;
//    }
//    return -1;
//}
//int Index::DeleteArc(string name, DataNode v, DataNode w) {
//    auto target=find(graphs.begin(),graphs.end(),name);
//    if(target!=graphs.end()){
//        //find target
//        auto &targetData=target.base()->data;
//        int vNum=getSequence(name,v.dataName),wNum=getSequence(name,w.dataName);
//        if(vNum!=-1&&wNum!=-1){
//            auto p=find(targetData[vNum].edgeList.begin(),targetData[vNum].edgeList.end(),wNum);
//            if(p!=targetData[vNum].edgeList.end()) {
//                targetData[vNum].edgeList.erase(p);
//                p = find(targetData[wNum].edgeList.begin(), targetData[wNum].edgeList.end(), vNum);
//                if (p != targetData[wNum].edgeList.end()) {
//                    targetData[wNum].edgeList.erase(p);
//                    return 1;
//                }
//            }
//        }
////        for(auto &x:targetData){
////            if(x.dataName==v.dataName){
////                for(auto &y:targetData){
////                    if(y.dataName==w.dataName){
////
////                    }
////                }
////            }
////        }
//    }
//    return -1;
//}
//int visitPrint(DataNode &x){
//    cout << x.dataName << "  " <<x.dataContent<< endl;
////    x.flag=1;
////    fflush(stdout);
//    return 1;
//}
//int Index::DFSTraverse(string name, Visit visit) {
//    auto target=find(graphs.begin(),graphs.end(),name);
//    if(target!=graphs.end()){
//        //find target
//        auto &targetData=target.base()->data;
//        visitFunc=visit;
//        for(DataNode &x:targetData){
//            DFSStep(x,targetData);
//        }
//        for(DataNode &x:targetData){
//            x.clearFlag();
//        }
//        return 1;
//    }
//    return -1;
//}
//int Index::DFSStep(DataNode &x,vector <DataNode> &targetData) {
//    if(x.flag==1)
//        return 0;
//    visitFunc(x);
//    x.flag=1;
//    for(int relateNum:x.edgeList){
//        DFSStep(targetData[relateNum],targetData);
//    }
//}
//int Index::BFSTraverse(string name, Visit visit) {
//    auto target=find(graphs.begin(),graphs.end(),name);
//    if(target!=graphs.end()){
//        //find target
//        auto &targetData=target.base()->data;
//        visitFunc=visit;
//        for(DataNode &x:targetData){
//            if(x.flag==0){
//                visitFunc(x);
//                x.flag=1;
//            }
//            BFSStep(x,targetData);
//        }
//        for(DataNode &x:targetData){
//            x.clearFlag();
//        }
//        return 1;
//    }
//    return -1;
//}
//int Index::BFSStep(DataNode &x,vector <DataNode> &targetData) {
////    if(x.flag==1)
////        return 0;
//    bool currentFlag=0;
//    for(int relateNum:x.edgeList){
//        if(targetData[relateNum].flag==0){
//            visitFunc(targetData[relateNum]);
//            targetData[relateNum].flag=1;
//            currentFlag=1;
//        }
//    }
//    if(currentFlag==0)
//        return 0;
//    for(int relateNum:x.edgeList){
//        BFSStep(targetData[relateNum],targetData);
//    }
//}
//int Index::Save() {
//    fstream localFile;
//    localFile.open("data.dat",ios::out);
//    localFile << graphs.size() << endl;
//    for(Graph currentGraph:graphs){
//        localFile << currentGraph.name << endl << currentGraph.data.size() << endl;
//        for(DataNode currentDataNode:currentGraph.data){
//            localFile << currentDataNode.dataName << endl <<currentDataNode.dataContent << endl << currentDataNode.edgeList.size() << endl;
//            for(int currentEdge:currentDataNode.edgeList){
//                localFile << currentEdge << endl;
//            }
//        }
//    }
//    return 1;
//}
//int Index::Load() {
//    fstream localFile;
//    localFile.open("data.dat",ios::in);
//    graphs.clear();
//    int graphSize;
//    localFile >> graphSize;
//    for(int i1=0;i1<graphSize;i1++){
//        auto currentGraph=graphs.emplace(graphs.end());
//        localFile >> currentGraph.base()->name;
//        int graphSzie;
//        localFile >> graphSize;
//        for(int i2=0;i2<graphSize;i2++){
//            auto currentDataNode=currentGraph.base()->data.emplace(currentGraph.base()->data.end());
//            localFile >> currentDataNode.base()->dataName >> currentDataNode.base()->dataContent;
//            int edgeSize;
//            localFile >> edgeSize;
//            for(int i3=0;i3<edgeSize;i3++){
//                auto currentEdge=currentDataNode.base()->edgeList.emplace(currentDataNode.base()->edgeList.end());
//                localFile >> *currentEdge;
//            }
//        }
//    }
//}
//int main(void){
//    Index index;
//    int temp;
//    for(;;) {
//        cout << "---------------------------------------------------------" << endl;
//        cout << "1.CreateGraph              2.DestroyGraph                " << endl;
//        cout << "3.LocateVex                4.GetVex                      " << endl;
//        cout << "5.PutVex                   6.FirstAdjVex                 " << endl;
//        cout << "7.NextAdjVex               8.InsertVex                   " << endl;
//        cout << "9.DeleteVex                10.InsertArc                  " << endl;
//        cout << "11.DeleteArc               12.DFSTraverse                " << endl;
//        cout << "13.BFSTraverse                                           " << endl;
//        cout << "14.Save                    15.Load                       " << endl;
//        cout << "0.Exit                                                   " << endl;
//        cout << "---------------------------------------------------------" << endl;
//        cin >> temp;
//        if (cin.fail()) {
//            cout << "Invalid Input" << endl;
//            cin.clear();
//            cin.sync();
//            fflush(stdin);
//            getchar();
//            continue;
//        }
//        switch (temp) {
//            case 1: {
//                DataSet tempData;
//                EdgeSet tempEdge;
//                string name;
//                cout << "Input Name" << endl;
//                cin >> name;
//                cout << "Input DataNode Size and Content" << endl;
//                tempData.setDataSet();
//                cout << "Input Edge Size and Content" << endl;
//                tempEdge.setEdgeSet();
//                int result=index.CreateGraph(name, tempData, tempEdge);
//                if(result==1)
//                    cout << "Operation Succeeded" << endl;
//                else if(result==-1)
//                    cout << "Operation Failed" << endl;
//                break;
//            }
//
//            case 2:{
//                string name;
//                cout << "Input Name" << endl;
//                cin >> name;
//                int result=index.DestroyGraph(name);
//                if(result==1)
//                    cout << "Operation Succeeded" << endl;
//                else if(result==-1)
//                    cout << "Operation Failed" << endl;
//                break;
//            }
//            case 3:{
//                string name;
//                cout << "Input Name" << endl;
//                cin >> name;
//                DataNode compareData;
//                string dataName;
//                int dataContent;
//                cout << "Input Target's Name And Content" << endl;
//                cin >> dataName >> dataContent;
//                compareData.setDataNodes(dataName,dataContent);
//                int result=index.LocateVex(name,compareData);
//                if(result!=-1){
//                    cout << result <<endl;
//                    cout << "Operation Succeeded" << endl;
//                }
//                else
//                    cout << "Operation Failed" << endl;
//                break;
//            }
//            case 4:{
//                string name;
//                cout << "Input Name" << endl;
//                cin >> name;
//                string dataName;
//                cout << "Input DataName" << endl;
//                cin >> dataName;
//                int result=index.GetVex(name,dataName);
//                if(result!=-1){
//                    cout << result <<endl;
//                    cout << "Operation Succeeded" << endl;
//                }
//                else
//                    cout << "Operation Failed" << endl;
//                break;
//
//            }
//            case 5:{
//                string name;
//                cout << "Input Name" << endl;
//                cin >> name;
//                DataNode compareData;
//                string dataName;
//                int dataContent;
//                int newContent;
//                cout << "Input Target's Name And Content" << endl;
//                cin >> dataName >> dataContent ;
//                cout << "Input New Content" << endl;
//                cin >> newContent;
//                compareData.setDataNodes(dataName,dataContent);
//                int result=index.PutVex(name,compareData,newContent);
//                if(result==1)
//                    cout << "Operation Succeeded" << endl;
//                else if(result==-1)
//                    cout << "Operation Failed" << endl;
//                break;
//            }
//            case 6:{
//                string name;
//                cout << "Input Name" << endl;
//                cin >> name;
//                DataNode compareData;
//                string dataName;
//                int dataContent;
//                cout << "Input Target's Name And Content" << endl;
//                cin >> dataName >> dataContent ;
//                compareData.setDataNodes(dataName,dataContent);
//                DataNode result=index.FirstAdjVex(name,compareData);
//                if(result.dataName!=""){
//                    cout << result.dataName << endl << result.dataContent << endl;
//                }
//                else if(result.dataContent==-1){
//                    cout << "No Match Node" <<endl;
//                }
//                else
//                    cout << "Operation Failed" << endl;
//                break;
//            }
//            case 7:{
//                string name;
//                cout << "Input Name" << endl;
//                cin >> name;
//                DataNode compareData;
//                string dataName;
//                int dataContent;
//                cout << "Input Base Target's Name And Content" << endl;
//                cin >> dataName >> dataContent ;
//                compareData.setDataNodes(dataName,dataContent);
//                DataNode firstData;
//                string firstDataName;
//                int firstDataContent;
//                cout << "Input First Target's Name And Content" << endl;
//                cin >> firstDataName >> firstDataContent ;
//                firstData.setDataNodes(firstDataName,firstDataContent);
//                DataNode result=index.NextAdjVex(name,compareData,firstData);
//                if(result.dataName!=""){
//                    cout << result.dataName << endl << result.dataContent << endl;
//                }
//                else if(result.dataContent==-1){
//                    cout << "No Match Node" <<endl;
//                }
//                else
//                    cout << "Operation Failed" << endl;
//                break;
//            }
//            case 8:{
//                string name;
//                cout << "Input Name" << endl;
//                cin >> name;
//                DataNode compareData;
//                string dataName;
//                int dataContent;
//                cout << "Input Target's Name And Content" << endl;
//                cin >> dataName >> dataContent ;
//                compareData.setDataNodes(dataName,dataContent);
//                int result=index.InsertVex(name,compareData);
//                if(result==1)
//                    cout << "Operation Succeeded" << endl;
//                else if(result==-1)
//                    cout << "Operation Failed" << endl;
//                break;
//            }
//            case 9:{
//                string name;
//                cout << "Input Name" << endl;
//                cin >> name;
//                DataNode compareData;
//                string dataName;
//                int dataContent;
//                cout << "Input Target's Name And Content" << endl;
//                cin >> dataName >> dataContent ;
//                compareData.setDataNodes(dataName,dataContent);
//                int result=index.DeleteVex(name,compareData);
//                if(result==1)
//                    cout << "Operation Succeeded" << endl;
//                else if(result==-1)
//                    cout << "Operation Failed" << endl;
//                break;
//            }
//            case 10:{
//                string name;
//                cout << "Input Name" << endl;
//                cin >> name;
//                DataNode firstData;
//                string dataName;
//                int dataContent;
//                cout << "Input First Target's Name And Content" << endl;
//                cin >> dataName >> dataContent ;
//                firstData.setDataNodes(dataName,dataContent);
//                DataNode secondData;
//                string secondDataName;
//                int secondDataContent;
//                cout << "Input Second Target's Name And Content" << endl;
//                cin >> secondDataName >> secondDataContent ;
//                secondData.setDataNodes(secondDataName,secondDataContent);
//                int result=index.InsertArc(name,firstData,secondData);
//                if(result==1)
//                    cout << "Operation Succeeded" << endl;
//                else if(result==-1)
//                    cout << "Operation Failed" << endl;
//                break;
//            }
//            case 11:{
//                string name;
//                cout << "Input Name" << endl;
//                cin >> name;
//                DataNode firstData;
//                string dataName;
//                int dataContent;
//                cout << "Input First Target's Name And Content" << endl;
//                cin >> dataName >> dataContent ;
//                firstData.setDataNodes(dataName,dataContent);
//                DataNode secondData;
//                string secondDataName;
//                int secondDataContent;
//                cout << "Input Second Target's Name And Content" << endl;
//                cin >> secondDataName >> secondDataContent ;
//                secondData.setDataNodes(secondDataName,secondDataContent);
//                int result=index.DeleteArc(name,firstData,secondData);
//                if(result==1)
//                    cout << "Operation Succeeded" << endl;
//                else if(result==-1)
//                    cout << "Operation Failed" << endl;
//                break;
//            }
//            case 12:{
//                string name;
//                cout << "Input Name" << endl;
//                cin >> name;
//                int result=index.DFSTraverse(name,visitPrint);
//                if(result==1)
//                    cout << "Operation Succeeded" << endl;
//                else if(result==-1)
//                    cout << "Operation Failed" << endl;
//                break;
//            }
//            case 13:{
//                string name;
//                cout << "Input Name" << endl;
//                cin >> name;
//                int result=index.BFSTraverse(name,visitPrint);
//                if(result==1)
//                    cout << "Operation Succeeded" << endl;
//                else if(result==-1)
//                    cout << "Operation Failed" << endl;
//                break;
//            }
//            case 14:{
//                index.Save();
//                cout << "Operation Succeeded" << endl;
//                break;
//            }
//            case 15:{
//                index.Load();
//                cout << "Operation Succeeded" << endl;
//                break;
//            }
//            case 0:{
//                return 1;
//            }
//            default:{
//                cout << "Input Invalid" << endl;
//                break ;
//            }
//        }
//
//    }
//
////    DataSet x;
////    x.setDataSet();
////    EdgeSet e;
////    e.setEdgeSet();
////    index.CreateGraph("g1",x,e);
////    index.CreateGraph("g2",x,e);
////    index.DestroyGraph("g2");
//
////    DataNode test,test2;
////    test.setDataNodes("a1",1);
////    test2.setDataNodes("a4",4);
////    cout << index.LocateVex("g1",test);
////    cout << index.GetVex("g1","a3");
////    index.PutVex("g1",test,666);
////    auto p=index.FirstAdjVex("g1",test);
////    auto p=index.NextAdjVex("g1",test,test2);
////    index.InsertVex("g1",test2);
////    index.DeleteVex("g1",test2);
//
//
////     index.InsertArc("g1",test,test2);
////     auto p=index.DeleteArc("g1",test,test2);
////    index.DFSTraverse("g1",visitPrint);
////    index.BFSTraverse("g1",visitPrint);
//    return 0;
//}