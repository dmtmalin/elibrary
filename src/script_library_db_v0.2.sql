CREATE GENERATOR gen_object_id;
SET GENERATOR gen_object_id TO 0;

CREATE GENERATOR gen_booktag_id;
SET GENERATOR gen_booktag_id TO 0;

CREATE GENERATOR gen_log_id;
SET GENERATOR gen_log_id TO 0;

CREATE GENERATOR gen_type_id;
SET GENERATOR gen_type_id TO 0;

CREATE GENERATOR gen_file_id;
SET GENERATOR gen_file_id TO 0;

CREATE GENERATOR gen_book_id;
SET GENERATOR gen_book_id TO 0;

CREATE GENERATOR gen_blob_id;
SET GENERATOR gen_blob_id TO 0;

CREATE GENERATOR gen_userfindtag_id;
SET GENERATOR gen_userfindtag_id TO 0;

CREATE GENERATOR gen_usersbook_id;
SET GENERATOR gen_usersbook_id TO 0;

CREATE TABLE Objects (
  ObjectId INTEGER NOT NULL,
  Code VARCHAR(5),
  Name VARCHAR(50),
  CONSTRAINT PK_Objects_ObjectId PRIMARY KEY (ObjectId)
);

CREATE TABLE Logs (
  LogId INTEGER NOT NULL,
  BookId INTEGER NOT NULL,
  DateLog DATE,
  TimeLog TIME,
  DateTimeLog TIMESTAMP,
  CONSTRAINT PK_Logs_LogId PRIMARY KEY (LogId)
);

CREATE TABLE BooksTags (
  BookTagId INTEGER NOT NULL,
  TypeTagId INTEGER NOT NULL,
  BookId INTEGER NOT NULL,
  CONSTRAINT PK_BooksTags_BookTagId PRIMARY KEY (BookTagId)
);

CREATE TABLE Files (
  FileId INTEGER NOT NULL,
  BookId INTEGER NOT NULL,
  TypeFormatId INTEGER NOT NULL,
  Name VARCHAR(250),
  SizeKB BIGINT,
  SizeKB_zip BIGINT,
  MD5 CHAR(32),
  CONSTRAINT PK_Files_FileId PRIMARY KEY (FileId)
);

CREATE TABLE Blobs (
  BlobId INTEGER NOT NULL,
  FileId INTEGER NOT NULL,
  BytesArray BLOB SUB_TYPE 0 NOT NULL,
  CONSTRAINT PK_Blobs_BlobId PRIMARY KEY (BlobId)
);

CREATE TABLE Books (
  BookId INTEGER NOT NULL,
  TypeThemeId INTEGER NOT NULL,
  Name VARCHAR(256),
  Author VARCHAR(256),
  Description VARCHAR(1024),
  CONSTRAINT PK_Books_BookId PRIMARY KEY (BookId)
);

CREATE TABLE Types (
  TypeId INTEGER NOT NULL,
  ObjectId INTEGER NOT NULL,
  Name VARCHAR(256),  
  CONSTRAINT PK_Types_TypeId PRIMARY KEY (TypeId)
);

CREATE TABLE UserFindTags (
  UserFindTagId INTEGER NOT NULL,
  TypeTagId INTEGER NOT NULL,
  CONSTRAINT PK_UserFindTags_UserFindTagId PRIMARY KEY (UserFindTagId)
);

CREATE TABLE UsersBooks (
  UsersBookId INTEGER NOT NULL,
  BookId INTEGER NOT NULL,
  TypeId INTEGER NOT NULL,
  CONSTRAINT PK_UsersBook_UsersBookId PRIMARY KEY (UsersBookId)
);

CREATE INDEX IX_Types_Name ON Types
  (Name);
  
CREATE INDEX IX_Objects_Code ON Objects
  (Code);

CREATE INDEX IX_Books_Name ON Books
  (Name);

CREATE INDEX IX_Books_Author ON Books
  (Author);

CREATE INDEX IX_Files_Name ON Files
  (Name);
  
CREATE INDEX IX_Files_MD5 ON Files
  (MD5);
  
CREATE INDEX IX_Log_DateLog ON Logs
  (DateLog);
  
CREATE INDEX IX_Log_TimeLog ON Logs
  (TimeLog);  
  

SET TERM ^ ;

CREATE TRIGGER trgBOOKS_BI_V3 FOR BOOKS
active before insert position 0
AS
BEGIN
    if((new.BOOKID is null) or (new.BOOKID = 0)) then
    begin
        new.BOOKID = gen_id(GEN_BOOK_ID, 1);
    end
END
^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE TRIGGER trgUSERFINDTAGS_BI_V3 FOR USERFINDTAGS
active before insert position 0
AS
BEGIN
    if((new.USERFINDTAGID is null) or (new.USERFINDTAGID = 0)) then
    begin
        new.USERFINDTAGID = gen_id(GEN_USERFINDTAG_ID, 1);
    end
END
^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE TRIGGER trgFILES_BI_V3 FOR FILES
active before insert position 0
AS
BEGIN
    if((new.FILEID is null) or (new.FILEID = 0)) then
    begin
        new.FILEID = gen_id(GEN_FILE_ID, 1);
    end
END
^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE TRIGGER trgOBJECTS_BI_V3 FOR OBJECTS
active before insert position 0
AS
BEGIN
    if((new.OBJECTID is null) or (new.OBJECTID = 0)) then
    begin
        new.OBJECTID = gen_id(GEN_OBJECT_ID, 1);
    end
END
^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE TRIGGER trgTYPES_BI_V3 FOR TYPES
active before insert position 0
AS
BEGIN
    if((new.TYPEID is null) or (new.TYPEID = 0)) then
    begin
        new.TYPEID = gen_id(GEN_TYPE_ID, 1);
    end
END
^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE TRIGGER trgBLOBS_BI_V3 FOR BLOBS
active before insert position 0
AS
BEGIN
    if((new.BLOBID is null) or (new.BLOBID = 0)) then
    begin
        new.BLOBID = gen_id(GEN_BLOB_ID, 1);
    end
END
^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE TRIGGER trgBOOKSTAGS_BI_V3 FOR BOOKSTAGS
active before insert position 0
AS
BEGIN
    if((new.BOOKTAGID is null) or (new.BOOKTAGID = 0)) then
    begin
        new.BOOKTAGID = gen_id(GEN_BOOKTAG_ID, 1);
    end
END
^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE TRIGGER trgLOGS_BI_V3 FOR LOGS
active before insert position 0
AS
BEGIN
    if((new.LOGID is null) or (new.LOGID = 0)) then
    begin
        new.LOGID = gen_id(GEN_LOG_ID, 1);
    end
END
^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE TRIGGER trgUSERSBOOKS_BI_V3 FOR USERSBOOKS
active before insert position 0
AS
BEGIN
    if((new.USERSBOOKID is null) or (new.USERSBOOKID = 0)) then
    begin
        new.USERSBOOKID = gen_id(GEN_USERSBOOK_ID, 1);
    end
END
^

SET TERM ; ^ --;

ALTER TABLE Types ADD CONSTRAINT Objects_Types
  FOREIGN KEY (ObjectId)
  REFERENCES Objects (ObjectId);

ALTER TABLE BooksTags ADD CONSTRAINT Books_BooksTags
  FOREIGN KEY (BookId)
  REFERENCES Books (BookId)
  ON DELETE CASCADE;

ALTER TABLE Files ADD CONSTRAINT Books_Files
  FOREIGN KEY (BookId)
  REFERENCES Books (BookId)
  ON DELETE CASCADE;

ALTER TABLE Blobs ADD CONSTRAINT Files_Blobs
  FOREIGN KEY (FileId)
  REFERENCES Files (FileId)
  ON DELETE CASCADE;

ALTER TABLE BooksTags ADD CONSTRAINT Types_BooksTags
  FOREIGN KEY (TypeTagId)
  REFERENCES Types (TypeId);

ALTER TABLE Files ADD CONSTRAINT Types_Files
  FOREIGN KEY (TypeFormatId)
  REFERENCES Types (TypeId);

ALTER TABLE Logs ADD CONSTRAINT Books_Logs
  FOREIGN KEY (BookId)
  REFERENCES Books (BookId)
  ON DELETE CASCADE;

ALTER TABLE Books ADD CONSTRAINT Types_Books
  FOREIGN KEY (TypeThemeId)
  REFERENCES Types (TypeId);
  
ALTER TABLE UserFindTags ADD CONSTRAINT Types_UserFindTags
  FOREIGN KEY (TypeTagId)
  REFERENCES Types (TypeId);
 
ALTER TABLE UsersBooks ADD CONSTRAINT Types_UsersBooks
  FOREIGN KEY (TypeId)
  REFERENCES Types (TypeId);
 
ALTER TABLE UsersBooks ADD CONSTRAINT Books_UsersBooks
  FOREIGN KEY (BookId)
  REFERENCES Books (BookId)
  ON DELETE CASCADE;

SET TERM ^ ;

CREATE PROCEDURE FIND_TYPEID (
    NAME_TYPE Varchar(256),
    CODE_OBJECT Varchar(5) )
RETURNS (
    TYPEID Integer )
AS
BEGIN
  SELECT FIRST 1 t.TYPEID
  FROM TYPES t
  INNER JOIN OBJECTS o ON t.OBJECTID = o.OBJECTID
  WHERE t.NAME = :name_type AND
        o.CODE = :code_object
  INTO :typeid;
END
^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE PROCEDURE ADD_TYPE (
    NAME_TYPE Varchar(256),
    CODE_OBJECT Varchar(5) )
RETURNS (
    TYPEID Integer )
AS
DECLARE VARIABLE OBJECTID integer;
BEGIN
  SELECT FIRST 1 OBJECTID
  FROM OBJECTS
  WHERE CODE = :code_object
  INTO :objectid;
  IF(objectid is NOT NULL) THEN
  BEGIN
    insert into TYPES (OBJECTID, NAME)
    values (:objectid, :name_type);

    SELECT GEN_ID(GEN_TYPE_ID, 0)
    FROM RDB$DATABASE
    INTO :typeid;
  END
END
^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE PROCEDURE ADD_FILE (
    BOOKID Integer,
    SIZEKB Bigint,
	SIZEKB_ZIP BigInt,	
    NAME Varchar(256),
    FORMAT Varchar(50),
    BYTESARRAY Blob sub_type 0,
	MD5 Char(32))
RETURNS (
    FILEID Integer )
AS
DECLARE VARIABLE TYPEFORMATID integer;
DECLARE VARIABLE BLOBID integer;
BEGIN
    EXECUTE PROCEDURE FIND_TYPEID(:format, 'F') RETURNING_VALUES :typeformatid;
    IF(typeformatid IS NULL) then
        EXECUTE PROCEDURE ADD_TYPE(:format, 'F') RETURNING_VALUES :typeformatid;
    IF(typeformatid IS NOT NULL) then
    BEGIN
        INSERT INTO FILES (BOOKID, TYPEFORMATID, NAME, SIZEKB, SIZEKB_ZIP, MD5)
        VALUES (:bookid, :typeformatid, :name, :sizekb, :sizekb_zip, :md5);

        SELECT GEN_ID(GEN_FILE_ID, 0)
        FROM RDB$DATABASE
        INTO :fileid;

        INSERT INTO BLOBS (FILEID, BYTESARRAY)
        VALUES (:fileid, :bytesarray);
    END
END
^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE PROCEDURE ADD_BOOKTAG (
    BOOKID Integer,
    NAME_TAG Varchar(256) )
RETURNS (
    BOOKTAGID Integer )
AS
DECLARE VARIABLE TYPETAGID integer;
BEGIN
    EXECUTE PROCEDURE FIND_TYPEID(:name_tag, 'TG') RETURNING_VALUES :typetagid;
    IF(typetagid IS NULL) then
        EXECUTE PROCEDURE ADD_TYPE(:name_tag, 'TG') RETURNING_VALUES :typetagid;
    IF(typetagid IS NOT NULL) then
    BEGIN
        INSERT INTO BOOKSTAGS (BOOKID, TYPETAGID)
        VALUES (:bookid, :typetagid);

        SELECT GEN_ID(GEN_BOOKTAG_ID, 0)
        FROM RDB$DATABASE
        INTO :booktagid;
    END
END
^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE PROCEDURE ADD_BOOK (
    NAME Varchar(256),
    AUTHOR Varchar(256),
    THEME Varchar(256),
    DESCRIPTION Varchar(1024) )
RETURNS (
    BOOKID Integer )
AS
DECLARE VARIABLE TYPETHEMEID integer;
BEGIN
    EXECUTE PROCEDURE FIND_TYPEID(:theme, 'T') RETURNING_VALUES :typethemeid;
    IF(typethemeid IS NULL) then
        EXECUTE PROCEDURE ADD_TYPE(:theme, 'T') RETURNING_VALUES :typethemeid;
    IF(typethemeid IS NOT NULL) then
    BEGIN
        INSERT INTO BOOKS (TYPETHEMEID, NAME, AUTHOR, DESCRIPTION)
        VALUES (:typethemeid, :name, :author, :description);

        SELECT GEN_ID(GEN_BOOK_ID, 0)
        FROM RDB$DATABASE
        INTO :bookid;

        INSERT INTO LOGS (BOOKID, DATELOG, TIMELOG, DATETIMELOG)
        VALUES (:bookid, current_date, current_time, current_timestamp);
    END
END
^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE PROCEDURE DELETE_USERFINDTAGS 
RETURNS (
    RESULT INTEGER)
AS
BEGIN
  RESULT = 0;
  DELETE FROM USERFINDTAGS;
  RESULT = 1;  
END^

SET TERM ; ^

SET TERM ^ ;

CREATE PROCEDURE ADD_TO_USERFINDTAGS (
    TAGID integer) 
RETURNS (
    ID integer)
AS 
BEGIN
  IF(tagid is NOT NULL) then
  BEGIN
    INSERT INTO USERFINDTAGS (TYPETAGID)
    VALUES (:tagid);
    
    SELECT GEN_ID(GEN_USERFINDTAG_ID, 0)
    FROM RDB$DATABASE
    INTO :id;
  END 
END^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE PROCEDURE GET_BLOB (
    FILEID Integer )
RETURNS (
    ID Integer,
	MD5 Varchar(32),
    FILENAME Varchar(306),
    R_BLOB Blob sub_type 0 )
AS
BEGIN
  SELECT FIRST 1
    bl.BLOBID,
	f.MD5,
    f.NAME,
    bl.BYTESARRAY
  FROM FILES f
  INNER JOIN BLOBS bl ON f.FILEID = bl.FILEID
  WHERE f.FILEID = :fileid
  INTO
    :id,
	:md5,
    :filename,
    :r_blob;
END

^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE PROCEDURE GET_TAGS_BOOK (
    BOOKID Integer )
RETURNS (
    ID Integer,
    NAME Varchar(256) )
AS
BEGIN
    FOR SELECT
        t.TYPEID,
        t.NAME
    FROM TYPES t
    INNER JOIN BOOKSTAGS b on t.TYPEID = b.TYPETAGID
    WHERE b.BOOKID = :bookid
    INTO
        :id,
        :name
    DO BEGIN
        SUSPEND;
    END
END
^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE PROCEDURE GET_THEMES
RETURNS (
    ID Integer,
    NAME Varchar(256) )
AS
BEGIN
  FOR SELECT
    t.TYPEID,
    t.NAME
  FROM TYPES t
  INNER JOIN OBJECTS o ON t.OBJECTID = o.OBJECTID
  WHERE o.CODE = 'T'
  ORDER BY t.NAME ascending
  INTO
    :id,
    :name
  DO BEGIN
    SUSPEND;
  END
END
^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE PROCEDURE LIST_BOOK (
    NAME Varchar(256),
    AUTHOR Varchar(256),
    THEMEID Integer,
	DATEFROM Date,
    DATETO Date,
    FLAGTAG Integer )
RETURNS (
    R_DATE Varchar(10),
    R_TIME Varchar(8),
    R_BOOKID Integer,
    R_NAME Varchar(256),
    R_AUTHOR Varchar(256),
    R_THEME Varchar(256),
    R_DESCRIPTION Varchar(1024) )
AS
BEGIN
    FOR SELECT
        DISTINCT (b.BOOKID),
        CAST(l.DATELOG as Varchar(10)),
        SUBSTRING(CAST(l.TIMELOG as Varchar(13)) from 1 for 8),
        b.NAME,
        b.AUTHOR,
        tm.NAME,
        b.DESCRIPTION
    FROM BOOKS b
    LEFT OUTER JOIN TYPES tm ON b.TYPETHEMEID = tm.TYPEID
    LEFT OUTER JOIN BOOKSTAGS bt ON b.BOOKID = bt.BOOKID
    LEFT OUTER JOIN TYPES tg ON bt.TYPETAGID = tg.TYPEID
    LEFT OUTER JOIN LOGS l ON b.BOOKID = l.BOOKID
    WHERE
        (:name IS NULL OR b.NAME LIKE '%'||:name||'%') AND
        (:author IS NULL OR b.AUTHOR LIKE '%'||:author||'%') AND
        (:themeid IS NULL OR tm.TYPEID = :themeid ) AND
		(:datefrom IS NULL OR l.DATELOG >= :datefrom) AND
        (:dateto IS NULL OR l.DATELOG <= :dateto) AND
        (:flagtag IS NULL OR tg.TYPEID in (SELECT TYPETAGID FROM USERFINDTAGS))
    ORDER BY l.DATETIMELOG DESC
    INTO
        :r_bookid,
        :r_date,
        :r_time,
        :r_name,
        :r_author,
        :r_theme,
        :r_description
    DO BEGIN
        SUSPEND;
    END
END
^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE PROCEDURE GET_BLOBS (
    BOOKID Integer )
RETURNS (
    ID Integer,
	MD5 Varchar(32),
    FILENAME Varchar(306),
    R_BLOB Blob sub_type 0 )
AS
BEGIN
  FOR SELECT
    bl.BLOBID,
	f.MD5,
    f.NAME,
    bl.BYTESARRAY
  FROM BOOKS b
  INNER JOIN FILES f ON b.BOOKID = f.BOOKID
  INNER JOIN BLOBS bl ON f.FILEID = bl.FILEID
  WHERE b.BOOKID = :bookid
  INTO
    :id,
	:md5,
    :filename,
    :r_blob
  DO BEGIN
    SUSPEND;
  END
END

^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE PROCEDURE GET_FILES_BOOK (
    BOOKID Integer )
RETURNS (
    ID Integer,
    NAME Varchar(256),
    FORMAT Varchar(50),
    SIZEKB Bigint,
	SIZEKB_ZIP Bigint)
AS
BEGIN
  FOR SELECT
    f.FILEID,
    f.NAME,
    t.NAME,
    f.SIZEKB,
	f.SIZEKB_ZIP
  FROM FILES f
  INNER JOIN TYPES t on f.TYPEFORMATID = t.TYPEID
  WHERE f.BOOKID = :bookid
  INTO
    :id,
    :name,
    :format,
    :sizekb,
	:sizekb_zip
  DO BEGIN
    SUSPEND;
  END
END
^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE PROCEDURE GET_TAGS
RETURNS (
    ID Integer,
    NAME Varchar(256) )
AS
BEGIN
  FOR SELECT
    t.TYPEID,
    t.NAME
  FROM TYPES t
  INNER JOIN OBJECTS o ON t.OBJECTID = o.OBJECTID
  WHERE o.CODE = 'TG'
  ORDER BY t.NAME ascending
  INTO
    :id,
    :name
  DO BEGIN
    SUSPEND;
  END
END
^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE PROCEDURE ADD_LAST_VIEW_BOOK (
    BOOKID INTEGER ) 
RETURNS (
    USERSBOOKID INTEGER)
AS 
DECLARE VARIABLE TYPEID INTEGER;
BEGIN
	USERSBOOKID = -1;
    IF(bookid IS NOT NULL) THEN
    BEGIN
        EXECUTE PROCEDURE FIND_TYPEID('LV', 'UB') RETURNING_VALUES :typeid;    
        IF (typeid IS NOT NULL) then
        BEGIN
            IF(NOT EXISTS (
                        SELECT FIRST 1 ub.BOOKID
                        FROM USERSBOOKS ub
                        WHERE ub.BOOKID = :bookid AND
                              ub.TYPEID = :typeid)) THEN
            BEGIN
                INSERT INTO USERSBOOKS (BOOKID, TYPEID)
                VALUES (:bookid, :typeid);
            
                SELECT GEN_ID(GEN_USERSBOOK_ID, 0)
                FROM RDB$DATABASE
                INTO :usersbookid;
            END   
        END
    END
END^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE PROCEDURE ADD_LAST_ADD_BOOK (
    BOOKID INTEGER ) 
RETURNS (
    USERSBOOKID INTEGER)
AS 
DECLARE VARIABLE TYPEID INTEGER;
BEGIN
	USERSBOOKID = -1;
    IF(bookid IS NOT NULL) THEN
    BEGIN
        EXECUTE PROCEDURE FIND_TYPEID('LA', 'UB') RETURNING_VALUES :typeid;    
        IF (typeid IS NOT NULL) then
        BEGIN
           IF(NOT EXISTS (
                        SELECT FIRST 1 ub.BOOKID
                        FROM USERSBOOKS ub
                        WHERE ub.BOOKID = :bookid AND
                              ub.TYPEID = :typeid)) THEN
            BEGIN
                INSERT INTO USERSBOOKS (BOOKID, TYPEID)
                VALUES (:bookid, :typeid);
            
                SELECT GEN_ID(GEN_USERSBOOK_ID, 0)
                FROM RDB$DATABASE
                INTO :usersbookid;
            END   
        END
    END
END^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE PROCEDURE ADD_FAVORITE_BOOK (
    BOOKID INTEGER ) 
RETURNS (
    USERSBOOKID INTEGER)
AS 
DECLARE VARIABLE TYPEID INTEGER;
BEGIN
    USERSBOOKID = -1;
    IF(bookid IS NOT NULL) THEN
    BEGIN
        EXECUTE PROCEDURE FIND_TYPEID('F', 'UB') RETURNING_VALUES :typeid;    
        IF (typeid IS NOT NULL) then
        BEGIN
            IF(NOT EXISTS (
                        SELECT FIRST 1 ub.BOOKID
                        FROM USERSBOOKS ub
                        WHERE ub.BOOKID = :bookid AND
                              ub.TYPEID = :typeid)) THEN
            BEGIN
                INSERT INTO USERSBOOKS (BOOKID, TYPEID)
                VALUES (:bookid, :typeid);
            
                SELECT GEN_ID(GEN_USERSBOOK_ID, 0)
                FROM RDB$DATABASE
                INTO :usersbookid;
            END            
        END
    END
END^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE PROCEDURE LIST_LAST_ADD_BOOKS 
RETURNS (
    R_DATE Varchar(10),
    R_TIME Varchar(8),
    R_BOOKID Integer,
    R_NAME Varchar(256),
    R_AUTHOR Varchar(256),
    R_THEME Varchar(256),
    R_DESCRIPTION Varchar(1024) )
AS 
BEGIN
  FOR SELECT
        DISTINCT (b.BOOKID),
        CAST(l.DATELOG as Varchar(10)),
        SUBSTRING(CAST(l.TIMELOG as Varchar(13)) from 1 for 8),
        b.NAME,
        b.AUTHOR,
        tm.NAME,
        b.DESCRIPTION
    FROM BOOKS b
    LEFT OUTER JOIN TYPES tm ON b.TYPETHEMEID = tm.TYPEID
    LEFT OUTER JOIN BOOKSTAGS bt ON b.BOOKID = bt.BOOKID
    LEFT OUTER JOIN TYPES tg ON bt.TYPETAGID = tg.TYPEID
    LEFT OUTER JOIN LOGS l ON b.BOOKID = l.BOOKID
    
    INNER JOIN USERSBOOKS ub ON b.BOOKID = ub.BOOKID
    INNER JOIN TYPES t ON ub.TYPEID = t.TYPEID
    INNER JOIN OBJECTS o on t.OBJECTID = o.OBJECTID
    WHERE t.NAME = 'LA' AND o.CODE = 'UB'
    /*WHERE 
    (b.BOOKID in (
        SELECT ub.BOOKID
        FROM USERSBOOKS ub
        INNER JOIN TYPES t ON ub.TYPEID = t.TYPEID
        INNER JOIN OBJECTS o ON t.OBJECTID = o.OBJECTID
        WHERE t.NAME = 'LA' AND
              o.CODE = 'UB'))*/
    ORDER BY l.DATETIMELOG DESC
    INTO
        :r_bookid,
        :r_date,
        :r_time,
        :r_name,
        :r_author,
        :r_theme,
        :r_description
    DO BEGIN
        SUSPEND;
    END
END^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE PROCEDURE LIST_LAST_VIEW_BOOKS 
RETURNS (
    R_DATE Varchar(10),
    R_TIME Varchar(8),
    R_BOOKID Integer,
    R_NAME Varchar(256),
    R_AUTHOR Varchar(256),
    R_THEME Varchar(256),
    R_DESCRIPTION Varchar(1024) )
AS 
BEGIN
  FOR SELECT
        DISTINCT (b.BOOKID),
        CAST(l.DATELOG as Varchar(10)),
        SUBSTRING(CAST(l.TIMELOG as Varchar(13)) from 1 for 8),
        b.NAME,
        b.AUTHOR,
        tm.NAME,
        b.DESCRIPTION
    FROM BOOKS b
    LEFT OUTER JOIN TYPES tm ON b.TYPETHEMEID = tm.TYPEID
    LEFT OUTER JOIN BOOKSTAGS bt ON b.BOOKID = bt.BOOKID
    LEFT OUTER JOIN TYPES tg ON bt.TYPETAGID = tg.TYPEID
    LEFT OUTER JOIN LOGS l ON b.BOOKID = l.BOOKID
    
    INNER JOIN USERSBOOKS ub ON b.BOOKID = ub.BOOKID
    INNER JOIN TYPES t ON ub.TYPEID = t.TYPEID
    INNER JOIN OBJECTS o on t.OBJECTID = o.OBJECTID
    WHERE t.NAME = 'LV' AND o.CODE = 'UB'
   
    ORDER BY l.DATETIMELOG DESC
    INTO
        :r_bookid,
        :r_date,
        :r_time,
        :r_name,
        :r_author,
        :r_theme,
        :r_description
    DO BEGIN
        SUSPEND;
    END
END^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE PROCEDURE DELETE_LAST_VIEW_BOOKS
RETURNS ( 
    RESULT INTEGER)
AS 
BEGIN
  RESULT = 0;
  DELETE FROM USERSBOOKS ub
  WHERE ub.TYPEID in (
    SELECT t.TYPEID
    FROM TYPES t
    INNER JOIN OBJECTS o ON t.OBJECTID = o.OBJECTID
    WHERE t.NAME = 'LV' AND
          o.CODE = 'UB' );
  RESULT = 1;
END^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE PROCEDURE DELETE_LAST_ADD_BOOKS
RETURNS ( 
    RESULT INTEGER)
AS 
BEGIN
  RESULT = 0;
  DELETE FROM USERSBOOKS ub
  WHERE ub.TYPEID in (
    SELECT t.TYPEID
    FROM TYPES t
    INNER JOIN OBJECTS o ON t.OBJECTID = o.OBJECTID
    WHERE t.NAME = 'LA' AND
          o.CODE = 'UB' );
  RESULT = 1;
END^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE PROCEDURE LIST_FAVORITES_BOOKS 
RETURNS (
    R_DATE Varchar(10),
    R_TIME Varchar(8),
    R_BOOKID Integer,
    R_NAME Varchar(256),
    R_AUTHOR Varchar(256),
    R_THEME Varchar(256),
    R_DESCRIPTION Varchar(1024) )
AS 
BEGIN
  FOR SELECT
        DISTINCT (b.BOOKID),
        CAST(l.DATELOG as Varchar(10)),
        SUBSTRING(CAST(l.TIMELOG as Varchar(13)) from 1 for 8),
        b.NAME,
        b.AUTHOR,
        tm.NAME,
        b.DESCRIPTION
    FROM BOOKS b
    LEFT OUTER JOIN TYPES tm ON b.TYPETHEMEID = tm.TYPEID
    LEFT OUTER JOIN BOOKSTAGS bt ON b.BOOKID = bt.BOOKID
    LEFT OUTER JOIN TYPES tg ON bt.TYPETAGID = tg.TYPEID
    LEFT OUTER JOIN LOGS l ON b.BOOKID = l.BOOKID
    
    INNER JOIN USERSBOOKS ub ON b.BOOKID = ub.BOOKID
    INNER JOIN TYPES t ON ub.TYPEID = t.TYPEID
    INNER JOIN OBJECTS o on t.OBJECTID = o.OBJECTID
    WHERE t.NAME = 'F' AND o.CODE = 'UB'
   
    ORDER BY l.DATETIMELOG DESC
    INTO
        :r_bookid,
        :r_date,
        :r_time,
        :r_name,
        :r_author,
        :r_theme,
        :r_description
    DO BEGIN
        SUSPEND;
    END
END^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE PROCEDURE DELETE_FAVORITES_BOOKS
RETURNS ( 
    RESULT INTEGER)
AS 
BEGIN
  RESULT = 0;
  DELETE FROM USERSBOOKS ub
  WHERE ub.TYPEID in (
    SELECT t.TYPEID
    FROM TYPES t
    INNER JOIN OBJECTS o ON t.OBJECTID = o.OBJECTID
    WHERE t.NAME = 'F' AND
          o.CODE = 'UB' );
  RESULT = 1;
END^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE PROCEDURE DELETE_FAVORITES_BOOK (
    BOOKID INTEGER)
RETURNS ( 
    RESULT INTEGER)
AS 
DECLARE VARIABLE R_BOOKID INTEGER;
BEGIN
  if (EXISTS (
        SELECT ub.BOOKID
        FROM USERSBOOKS ub
        INNER JOIN TYPES t ON ub.TYPEID = t.TYPEID
        INNER JOIN OBJECTS o ON t.OBJECTID = o.OBJECTID        
        WHERE ub.BOOKID = :bookid AND
              t.NAME = 'F' AND
              o.CODE = 'UB')) THEN
  BEGIN
    DELETE FROM USERSBOOKS ub
    WHERE ub.BOOKID = :bookid;
    RESULT = 1;
  END ELSE
  BEGIN
    RESULT = -1;
  END    
END^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE PROCEDURE FIND_FILE_DUPLICATE (
    MD5 Char(32)) 
RETURNS (
    FILEID INTEGER,    
    NAME VARCHAR(256),
    AUTHOR VARCHAR(256),
    THEME VARCHAR(256) )
AS 
BEGIN
  FILEID = -1;
  SELECT FIRST 1
    f.FILEID,   
    b.NAME,
    b.AUTHOR,
    t.NAME
  FROM FILES f 
  INNER JOIN BOOKS b ON f.BOOKID = b.BOOKID
  INNER JOIN TYPES t ON b.TYPETHEMEID = t.TYPEID
  WHERE f.MD5 = :md5
  INTO :fileid, :name, :author, :theme;
END^

SET TERM ; ^ --;

SET TERM ^ ;
CREATE PROCEDURE UPDATE_BLOB (
    FILEID Integer,
    MD5 Char(32),
    SIZEKB Bigint,
    SIZEKB_ZIP Bigint,
    BYTESARRAY Blob sub_type 0 )
RETURNS (
    RESULT Integer )
AS
BEGIN  
  RESULT = 0;  
  IF (EXISTS (SELECT FIRST 1 f.FILEID
              FROM FILES f
              WHERE f.FILEID = :fileid)) THEN
  BEGIN
    UPDATE BLOBS bl
    SET bl.BYTESARRAY = :bytesarray
    WHERE bl.FILEID = :fileid;
  
    UPDATE FILES f
    SET f.MD5 = :md5,
    f.SIZEKB = :sizekb,
    f.SIZEKB_ZIP = :sizekb_zip
    WHERE f.FILEID = :fileid;    
  END
  RESULT = 1;
END^
SET TERM ; ^ --;

SET TERM ^ ;

CREATE PROCEDURE UPDATE_BOOK (
    BOOKID Integer,
    NAME Varchar(256),
    AUTHOR Varchar(256),
    THEME Varchar(256),
    DESCRIPTION Varchar(1024) ) 
RETURNS (
    RESULT Integer )
AS 
DECLARE VARIABLE TYPETHEMEID Integer;
BEGIN
  RESULT = 0;
  EXECUTE PROCEDURE FIND_TYPEID(:theme, 'T') RETURNING_VALUES :typethemeid;
  IF(typethemeid IS NULL) then
      EXECUTE PROCEDURE ADD_TYPE(:theme, 'T') RETURNING_VALUES :typethemeid;
  IF(typethemeid IS NOT NULL) then
  BEGIN
      UPDATE BOOKS b
      SET b.NAME = :name,
          b.AUTHOR = :author,
          b.TYPETHEMEID = :typethemeid,
          b.DESCRIPTION = :description
      WHERE b.BOOKID = :bookid;
      RESULT = 1;
  END
END^

SET TERM ; ^ --;

SET TERM ^ ;
CREATE PROCEDURE DELETE_TAGS (
    BOOKID Integer )
RETURNS (
    RESULT Integer )
AS
BEGIN
  RESULT = 0;
  DELETE FROM BOOKSTAGS bt
  WHERE bt.BOOKID = :bookid;
  RESULT = 1;  
END^
SET TERM ; ^ --;

SET TERM ^ ;

CREATE PROCEDURE DELETE_FILE ( 
    FILEID Integer) 
RETURNS (
    RESULT Integer)
AS
BEGIN
  RESULT = 0;
  DELETE FROM FILES f
  WHERE f.FILEID = :fileid;
  RESULT = 1;
END^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE PROCEDURE DELETE_BOOK (
    BOOKID Integer) 
RETURNS (
    RESULT Integer)
AS
BEGIN
  RESULT = 0;
  DELETE FROM BOOKS b
  WHERE b.BOOKID = :bookid;
  RESULT = 1;
END^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE PROCEDURE GET_BOOK (
    BOOKID Integer )
RETURNS (
    R_DATE Varchar(10),
    R_TIME Varchar(8),
    R_BOOKID Integer,
    R_NAME Varchar(256),
    R_AUTHOR Varchar(256),
    R_THEME Varchar(256),
    R_DESCRIPTION Varchar(1024) )
AS
BEGIN
    FOR SELECT
        DISTINCT (b.BOOKID),
        CAST(l.DATELOG as Varchar(10)),
        SUBSTRING(CAST(l.TIMELOG as Varchar(13)) from 1 for 8),
        b.NAME,
        b.AUTHOR,
        tm.NAME,
        b.DESCRIPTION
    FROM BOOKS b
    LEFT OUTER JOIN TYPES tm ON b.TYPETHEMEID = tm.TYPEID
    LEFT OUTER JOIN BOOKSTAGS bt ON b.BOOKID = bt.BOOKID
    LEFT OUTER JOIN TYPES tg ON bt.TYPETAGID = tg.TYPEID
    LEFT OUTER JOIN LOGS l ON b.BOOKID = l.BOOKID
    WHERE b.BOOKID = :bookid       
    ORDER BY l.DATETIMELOG DESC
    INTO
        :r_bookid,
        :r_date,
        :r_time,
        :r_name,
        :r_author,
        :r_theme,
        :r_description
    DO BEGIN
        SUSPEND;
    END
END^
SET TERM ; ^ --;

COMMIT WORK;

INSERT INTO OBJECTS (CODE, NAME) VALUES ('T',	'релю');
INSERT INTO OBJECTS (CODE, NAME) VALUES ('F',	'тнплюр');
INSERT INTO OBJECTS (CODE, NAME) VALUES ('TG',	'рец');
INSERT INTO OBJECTS (CODE, NAME) VALUES ('UB', 	'рно');

COMMIT WORK;

INSERT INTO TYPES (OBJECTID, NAME) VALUES ((SELECT OBJECTID FROM OBJECTS WHERE CODE = 'UB'), 'F'); --хгапюммне
INSERT INTO TYPES (OBJECTID, NAME) VALUES ((SELECT OBJECTID FROM OBJECTS WHERE CODE = 'UB'), 'LV'); --онякедмхи опнялнрп
INSERT INTO TYPES (OBJECTID, NAME) VALUES ((SELECT OBJECTID FROM OBJECTS WHERE CODE = 'UB'), 'LA'); --онякедмее днаюбкемхе