package top.zsj.webserver.domain;

import lombok.*;

import javax.annotation.Generated;

@AllArgsConstructor
@NoArgsConstructor
@Getter
@Setter
@ToString
public class UserData extends BaseData {

    public UserData(String nickname, String head, String password, String signature, Integer level, Boolean vip) {

        super(nickname, head, vip);
        this.password = password;
        this.signature = signature;
        this.level = level;
    }

    public UserData(Long id, String nickname, String head, String password, String signature, Integer level, Boolean vip) {
        super(id, nickname, head, vip);
        this.password = password;
        this.signature = signature;
        this.level = level;
    }

    private String password;
    private String signature;   // 签名
    private Integer level;
}
