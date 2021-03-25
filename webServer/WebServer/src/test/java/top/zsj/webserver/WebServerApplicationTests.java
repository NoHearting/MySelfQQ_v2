package top.zsj.webserver;

import org.apache.log4j.Logger;
import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;


@SpringBootTest
class WebServerApplicationTests {

	private static Logger logger = Logger.getLogger(WebServerApplicationTests.class);

	@Test
	void contextLoads() {


	}


	@Test
	void testLog4j(){
		logger.debug("debug info");
		logger.info("info info");
		logger.warn("warn info");
		logger.error("error info");
		logger.fatal("fatal error");
	}
}
