package top.zsj.webserver.domain;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@NoArgsConstructor
@AllArgsConstructor
@Data
public class BaseData {

    public BaseData(String nickname, String head, Boolean vip) {
        this.nickname = nickname;
        this.head = head;
        this.vip = vip;
    }

    private Long id;
    private String nickname;
    private String head;
    private Boolean vip;
}
