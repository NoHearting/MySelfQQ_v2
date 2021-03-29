package top.zsj.webserver.domain;

import com.sun.istack.internal.NotNull;
import lombok.*;

@AllArgsConstructor
@NoArgsConstructor
@Getter
@Setter
@ToString
public class GroupData extends BaseData {

    public GroupData(String nickname, String head, String introduce, Long belong, Integer maxSize, Integer currentNum, Boolean vip) {
        super(nickname, head, vip);
        this.introduce = introduce;
        this.belong = belong;
        this.maxSize = maxSize;
        this.currentNum = currentNum;
    }

    public GroupData(Long id, String nickname, String head, String introduce, Long belong, Integer maxSize, Integer currentNum, Boolean vip) {
        super(id, nickname, head, vip);
        this.introduce = introduce;
        this.belong = belong;
        this.maxSize = maxSize;
        this.currentNum = currentNum;
    }

    private String introduce;
    private Long belong;
    private Integer maxSize;
    private Integer currentNum;

}
