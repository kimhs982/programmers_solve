#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    int user_num = id_list.size();
    vector<int> answer(user_num);
    vector<vector<int>> modify_report(user_num);       // id_list에 담긴 id 순서대로 각 유저가 신고한 유저들의 정보를 저장
    vector<int> report_cnt_list(user_num);     // 각 이용자 id별로 신고 횟수를 저장
    
    // report 정리 -> modify_report, report_cnt_list 생성
    for(int i = 0; i < report.size(); i++) {
        int blank_pos = report[i].find(' ');
        string user_id = report[i].substr(0, blank_pos);
        string report_id = report[i].substr(blank_pos + 1);
        for(int j = 0; j < user_num; j++) {
            if(id_list[j] == user_id) {
                int l;
                for(l = 0; l < user_num; l++)
                    if((l != j)&&(id_list[l] == report_id)) {
                        modify_report[j].push_back(l);
                        report_cnt_list[l]++;
                        break;
                    }
                for(int m = 0; m < modify_report[j].size() - 1; m++)
                    if(modify_report[j][m] == modify_report[j].back()) {
                        modify_report[j].pop_back();
                        report_cnt_list[l]--;
                        break;
                    }
                break;
            }
        }
    }
    
    for(int i = 0; i < user_num; i++) {
        if(report_cnt_list[i] >= k) {
            for(int j = 0; j < user_num; j++)
                for(int l = 0; l < modify_report[j].size(); l++)
                    if(modify_report[j][l] == i) {
                        modify_report[j].erase(modify_report[j].begin() + l);
                        answer[j]++;
                        break;
                    }
        }
    }
    
    return answer;
}
