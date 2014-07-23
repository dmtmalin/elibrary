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

CREATE INDEX IX_Types_Name ON Types
  (Name);

CREATE INDEX IX_Books_Author ON Books
  (Author);

CREATE INDEX IX_Files_Name ON Files
  (Name);

CREATE INDEX IX_Books_Name ON Books
  (Name);

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
    NAME Varchar(256),
    FORMAT Varchar(50),
    BYTESARRAY Blob sub_type 0 )
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
        INSERT INTO FILES (BOOKID, TYPEFORMATID, NAME, SIZEKB)
        VALUES (:bookid, :typeformatid, :name, :sizekb);

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

        INSERT INTO LOGS (BOOKID, DATELOG, TIMELOG)
        VALUES (:bookid, current_date, current_time);
    END
END
^

SET TERM ; ^ --;

SET TERM ^ ;

CREATE PROCEDURE GET_BLOB (
    FILEID Integer )
RETURNS (
    ID Integer,
    FILENAME Varchar(306),
    R_BLOB Blob sub_type 0 )
AS
BEGIN
  SELECT FIRST 1
    f.FILEID,
    f.NAME,
    bl.BYTESARRAY
  FROM FILES f
  INNER JOIN BLOBS bl ON f.FILEID = bl.FILEID
  WHERE f.FILEID = :fileid
  INTO
    :id,
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
    TAGID Integer )
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
        tm.NAME THEME,
        b.DESCRIPTION
    FROM BOOKS b
    LEFT OUTER JOIN TYPES tm ON b.TYPETHEMEID = tm.TYPEID
    LEFT OUTER JOIN BOOKSTAGS bt ON b.BOOKID = bt.BOOKID
    LEFT OUTER JOIN TYPES tg ON bt.TYPETAGID = tg.TYPEID
    LEFT OUTER JOIN LOGS l ON b.BOOKID = l.BOOKID
    WHERE
        (:name IS NULL OR b.NAME LIKE :name||'%') AND
        (:author IS NULL OR b.AUTHOR LIKE :author||'%') AND
        (:themeid IS NULL OR tm.TYPEID = :themeid ) AND
        (:tagid IS NULL OR tg.TYPEID = :tagid)
    ORDER BY l.DATELOG, l.TIMELOG ASCENDING
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
    FILENAME Varchar(306),
    R_BLOB Blob sub_type 0 )
AS
BEGIN
  FOR SELECT
    bl.BLOBID,
    f.NAME,
    bl.BYTESARRAY
  FROM BOOKS b
  INNER JOIN FILES f ON b.BOOKID = f.BOOKID
  INNER JOIN BLOBS bl ON f.FILEID = bl.FILEID
  WHERE b.BOOKID = :bookid
  INTO
    :id,
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
    SIZEKB Bigint )
AS
BEGIN
  FOR SELECT
    f.FILEID,
    f.NAME,
    t.NAME,
    f.SIZEKB
  FROM FILES f
  INNER JOIN TYPES t on f.TYPEFORMATID = t.TYPEID
  WHERE f.BOOKID = :bookid
  INTO
    :id,
    :name,
    :format,
    :sizekb
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

COMMIT WORK;

INSERT INTO OBJECTS VALUES (1, 'T', 'релю');
INSERT INTO OBJECTS VALUES (2, 'F', 'тнплюр');
INSERT INTO OBJECTS VALUES (3, 'L', 'кнц');
INSERT INTO OBJECTS VALUES (4, 'TG', 'рец');